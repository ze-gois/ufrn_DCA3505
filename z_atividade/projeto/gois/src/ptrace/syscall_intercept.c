/**
 * @file syscall_intercept.c
 * @brief Implementation of system call interception for mutex operations
 *
 * This file implements functions for intercepting and analyzing system calls,
 * particularly focusing on futex calls that are used by pthread mutexes.
 */

#include "syscall_intercept.h"
#include "ptrace_attach.h"
#include "lock_tracker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <time.h>

// Maximum number of system calls we can handle
#define MAX_SYSCALL_NR 1024

// Verbose mode flag
static bool verbose = false;

// Array of syscall handlers
static syscall_handler_t syscall_handlers[MAX_SYSCALL_NR] = {0};

// Structure to track ongoing futex operations
typedef struct futex_operation {
    pid_t pid;
    void* futex_addr;
    int operation;
    int value;
    time_t timestamp;
    struct futex_operation* next;
} futex_operation_t;

// List of pending futex operations
static futex_operation_t* pending_futex_ops = NULL;

// Helper function to add a pending futex operation
static void add_pending_futex_op(pid_t pid, void* futex_addr, int operation, int value) {
    futex_operation_t* op = malloc(sizeof(futex_operation_t));
    if (!op) return;

    op->pid = pid;
    op->futex_addr = futex_addr;
    op->operation = operation;
    op->value = value;
    op->timestamp = time(NULL);
    op->next = pending_futex_ops;
    pending_futex_ops = op;
}

// Helper function to find and remove a pending futex operation
// static futex_operation_t* find_and_remove_pending_futex_op(pid_t pid, void* futex_addr) {
//     futex_operation_t** op_ptr = &pending_futex_ops;
//     futex_operation_t* op;

//     while (*op_ptr != NULL) {
//         op = *op_ptr;
//         if (op->pid == pid && op->futex_addr == futex_addr) {
//             *op_ptr = op->next;
//             return op;
//         }
//         op_ptr = &(op->next);
//     }
//     return NULL;
// }

// Helper function to clean up old pending operations
static void cleanup_old_futex_ops(void) {
    time_t now = time(NULL);
    futex_operation_t** op_ptr = &pending_futex_ops;
    futex_operation_t* op;

    while (*op_ptr != NULL) {
        op = *op_ptr;
        if (now - op->timestamp > 10) { // Remove operations older than 10 seconds
            *op_ptr = op->next;
            free(op);
        } else {
            op_ptr = &(op->next);
        }
    }
}

bool syscall_intercept_init(void) {
    // Register default handlers for the syscalls we're interested in
    syscall_register_handler(SYS_futex, syscall_handle_futex);
    syscall_register_handler(SYS_clone, syscall_handle_clone);
    syscall_register_handler(SYS_exit, syscall_handle_exit);
    syscall_register_handler(SYS_exit_group, syscall_handle_exit);

    pending_futex_ops = NULL;
    return true;
}

void syscall_intercept_cleanup(void) {
    // Clean up pending futex operations
    futex_operation_t* op = pending_futex_ops;
    while (op != NULL) {
        futex_operation_t* next = op->next;
        free(op);
        op = next;
    }
    pending_futex_ops = NULL;
}

bool syscall_register_handler(long syscall_nr, syscall_handler_t handler) {
    if (syscall_nr < 0 || syscall_nr >= MAX_SYSCALL_NR) {
        fprintf(stderr, "Syscall number %ld out of range\n", syscall_nr);
        return false;
    }

    syscall_handlers[syscall_nr] = handler;
    return true;
}

bool syscall_process(pid_t pid, long syscall_nr, bool entering) {
    if (verbose) {
        const char* phase = entering ? "entering" : "exiting";
        fprintf(stderr, "Process %d %s syscall %ld\n", pid, phase, syscall_nr);
    }

    // Periodically clean up old pending operations
    static time_t last_cleanup = 0;
    time_t now = time(NULL);
    if (now - last_cleanup > 30) { // Cleanup every 30 seconds
        cleanup_old_futex_ops();
        last_cleanup = now;
    }

    if (syscall_nr >= 0 && syscall_nr < MAX_SYSCALL_NR && syscall_handlers[syscall_nr] != NULL) {
        return syscall_handlers[syscall_nr](pid, entering);
    }

    return false; // Syscall not handled
}

bool syscall_handle_futex(pid_t pid, bool entering) {
    if (entering) {
        // When entering futex syscall, extract information about the operation
        unsigned long futex_uaddr = ptrace_get_syscall_arg(pid, 0);
        int futex_op = ptrace_get_syscall_arg(pid, 1);
        int futex_val = ptrace_get_syscall_arg(pid, 2);

        // Mask out flags to get the core operation
        int futex_cmd = futex_op & FUTEX_CMD_MASK;
        bool is_private = (futex_op & FUTEX_PRIVATE_FLAG) != 0;

        if (verbose) {
            const char* op_name = "UNKNOWN";
            switch (futex_cmd) {
                case FUTEX_WAIT: op_name = "WAIT"; break;
                case FUTEX_WAKE: op_name = "WAKE"; break;
                case FUTEX_WAIT_PRIVATE: op_name = "WAIT_PRIVATE"; break;
                case FUTEX_WAKE_PRIVATE: op_name = "WAKE_PRIVATE"; break;
            }
            fprintf(stderr, "Process %d futex %s%s: uaddr=%lx, val=%d\n",
                    pid, op_name, is_private ? " (private)" : "", futex_uaddr, futex_val);
        }

        // Process mutex-related futex operations
        if (futex_cmd == FUTEX_WAIT || futex_cmd == FUTEX_WAIT_PRIVATE) {
            // FUTEX_WAIT typically indicates a thread trying to acquire a locked mutex
            // The futex_val parameter contains the expected value of the futex

            // Store this operation for later correlation with the result
            add_pending_futex_op(pid, (void*)futex_uaddr, futex_cmd, futex_val);

            // Register this as a potential lock acquisition attempt
            // We use a heuristic: if futex_val != 0, it suggests the lock is currently held
            if (futex_val != 0) {
                if (verbose) {
                    fprintf(stderr, "Thread %d attempting to acquire mutex %p (currently locked with value %d)\n",
                            pid, (void*)futex_uaddr, futex_val);
                }

                // Register this as a lock acquisition attempt
                lock_tracker_register_thread(pid);
                lock_tracker_register_acquisition(pid, (void*)futex_uaddr, false);
            }

            return true;
        }
        else if (futex_cmd == FUTEX_WAKE || futex_cmd == FUTEX_WAKE_PRIVATE) {
            // FUTEX_WAKE typically indicates a mutex being unlocked
            // The futex_val parameter indicates how many waiters to wake

            if (verbose) {
                fprintf(stderr, "Thread %d releasing mutex %p (waking %d waiters)\n",
                        pid, (void*)futex_uaddr, futex_val);
            }

            // Register this as a lock release
            lock_tracker_register_thread(pid);
            lock_tracker_register_release(pid, (void*)futex_uaddr);

            return true;
        }
    } else {
        // When exiting futex syscall, check the result and correlate with entry
        long result = ptrace_get_syscall_result(pid);

        if (verbose) {
            fprintf(stderr, "Process %d futex returned %ld", pid, result);
            if (result == -EAGAIN) {
                fprintf(stderr, " (EAGAIN - value changed)");
            } else if (result == -ETIMEDOUT) {
                fprintf(stderr, " (ETIMEDOUT)");
            } else if (result == -EINTR) {
                fprintf(stderr, " (EINTR - interrupted)");
            } else if (result == 0) {
                fprintf(stderr, " (SUCCESS)");
            }
            fprintf(stderr, "\n");
        }

        // Try to find the corresponding entry operation
        // This is more complex since we don't have the futex address here
        // In a full implementation, we'd need to track this more carefully

        // For WAIT operations that succeeded (result == 0), the thread has acquired the lock
        // For WAIT operations that failed, the acquisition was unsuccessful

        // Clean up old operations periodically
        cleanup_old_futex_ops();
    }

    return true;
}

bool syscall_handle_clone(pid_t pid, bool entering) {
    if (entering) {
        // When entering clone, we can analyze the flags to determine if it's a thread
        unsigned long clone_flags = ptrace_get_syscall_arg(pid, 0);

        if (verbose) {
            fprintf(stderr, "Process %d calling clone with flags 0x%lx\n", pid, clone_flags);
        }

        // Check if this looks like pthread creation
        // CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | CLONE_SYSVSEM
        const unsigned long PTHREAD_FLAGS = 0x3d0f00;
        if ((clone_flags & PTHREAD_FLAGS) == PTHREAD_FLAGS) {
            if (verbose) {
                fprintf(stderr, "Detected pthread creation attempt\n");
            }
        }
    } else {
        // When exiting clone syscall, the return value is the new thread/process ID
        long new_pid = ptrace_get_syscall_result(pid);

        if (new_pid > 0) {
            if (verbose) {
                fprintf(stderr, "Process %d created new thread/process %ld\n", pid, new_pid);
            }

            // Register the new thread in our tracking system
            lock_tracker_register_thread((pid_t)new_pid);
        } else if (new_pid < 0) {
            if (verbose) {
                fprintf(stderr, "Process %d clone failed with error %ld\n", pid, -new_pid);
            }
        }
    }

    return true;
}

bool syscall_handle_exit(pid_t pid, bool entering) {
    if (entering) {
        // When a thread/process exits, clean up our data structures
        int exit_code = ptrace_get_syscall_arg(pid, 0);

        if (verbose) {
            fprintf(stderr, "Process %d exiting with code %d\n", pid, exit_code);
        }

        // Clean up any tracking information for this thread
        lock_tracker_unregister_thread(pid);

        // Remove any pending futex operations for this thread
        futex_operation_t** op_ptr = &pending_futex_ops;
        futex_operation_t* op;

        while (*op_ptr != NULL) {
            op = *op_ptr;
            if (op->pid == pid) {
                *op_ptr = op->next;
                free(op);
            } else {
                op_ptr = &(op->next);
            }
        }
    }

    return true;
}

void syscall_set_verbose(bool enable) {
    verbose = enable;
}
