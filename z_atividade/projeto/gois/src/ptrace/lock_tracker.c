/**
 * @file lock_tracker.c
 * @brief Implementation of the lock tracking system using ptrace
 *
 * This file implements the lock tracking system that monitors mutex operations
 * in a traced process, builds a lock dependency graph, and detects potential
 * deadlocks using the graph library.
 */

#include "lock_tracker.h"
#include "pthread_structures.h"
#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

// Print debugging information if verbose mode is enabled
static bool verbose = false;
#define verbose_print(fmt, ...) \
    do { if (verbose) fprintf(stderr, "[LOCKTRACKER] " fmt, ##__VA_ARGS__); } while (0)

// Global lock dependency graph
static graph_t* lock_graph = NULL;

// Enhanced structure to track locks held by a thread
typedef struct held_lock {
    void* lock_addr;             // Address of the lock
    time_t acquisition_time;     // When this lock was acquired
    int acquisition_order;       // Order in which this lock was acquired
    bool is_recursive;           // Whether this is a recursive acquisition
    int recursion_count;         // Number of times recursively acquired
    struct held_lock* next;      // Next lock in the thread's held lock list
} held_lock_t;

// Enhanced structure to track thread information
typedef struct thread_info {
    pid_t thread_id;             // Thread ID
    held_lock_t* held_locks;     // List of locks held by this thread
    int lock_count;              // Number of locks currently held
    int total_acquisitions;      // Total number of lock acquisitions
    time_t last_activity;        // Last time this thread acquired/released a lock
    void* waiting_for_lock;      // Lock this thread is currently waiting for (if any)
    bool is_blocked;             // Whether this thread is currently blocked
    struct thread_info* next;    // Next thread in the thread list
} thread_info_t;

// Structure to track lock information
typedef struct lock_info {
    void* lock_addr;             // Address of the lock
    pid_t owner_thread;          // Thread currently owning this lock (0 if none)
    int contention_count;        // Number of times this lock was contended
    time_t last_acquisition;     // Last time this lock was acquired
    bool is_contended;           // Whether this lock is currently contended
    struct lock_info* next;      // Next lock in the lock list
} lock_info_t;

// Global list of tracked threads and locks
static thread_info_t* threads = NULL;
static lock_info_t* locks = NULL;
static int global_acquisition_counter = 0;

// Helper function to format a pointer as a string for graph printing
static const char* format_ptr(void* ptr) {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "%p", ptr);
    return buffer;
}

// Helper function to find thread info
static thread_info_t* find_thread(pid_t thread_id) {
    thread_info_t* thread = threads;
    while (thread != NULL) {
        if (thread->thread_id == thread_id) {
            return thread;
        }
        thread = thread->next;
    }
    return NULL;
}

// Helper function to find lock info
static lock_info_t* find_lock_info(void* lock_addr) {
    lock_info_t* lock = locks;
    while (lock != NULL) {
        if (lock->lock_addr == lock_addr) {
            return lock;
        }
        lock = lock->next;
    }
    return NULL;
}

// Helper function to create or find lock info
static lock_info_t* find_or_create_lock_info(void* lock_addr) {
    lock_info_t* lock = find_lock_info(lock_addr);
    if (lock == NULL) {
        lock = malloc(sizeof(lock_info_t));
        if (lock != NULL) {
            lock->lock_addr = lock_addr;
            lock->owner_thread = 0;
            lock->contention_count = 0;
            lock->last_acquisition = 0;
            lock->is_contended = false;
            lock->next = locks;
            locks = lock;
        }
    }
    return lock;
}

// Helper function to check if a thread holds a lock
static held_lock_t* thread_find_held_lock(thread_info_t* thread, void* lock_addr) {
    held_lock_t* lock = thread->held_locks;
    while (lock != NULL) {
        if (lock->lock_addr == lock_addr) {
            return lock;
        }
        lock = lock->next;
    }
    return NULL;
}

// Helper function to check if a thread holds a lock (boolean version)
// static bool thread_holds_lock(thread_info_t* thread, void* lock_addr) {
//     return thread_find_held_lock(thread, lock_addr) != NULL;
// }

// Helper function to detect potential deadlocks using wait-for graph analysis
static bool detect_wait_for_cycle(void) {
    // Build a simplified wait-for graph
    // Each thread waiting for a lock creates an edge to the thread holding that lock

    int thread_count = 0;
    thread_info_t* thread = threads;
    while (thread != NULL) {
        thread_count++;
        thread = thread->next;
    }

    if (thread_count < 2) {
        return false; // Need at least 2 threads for deadlock
    }

    // Simple cycle detection using DFS
    thread = threads;
    while (thread != NULL) {
        if (thread->waiting_for_lock != NULL) {
            // Find who owns the lock this thread is waiting for
            lock_info_t* lock = find_lock_info(thread->waiting_for_lock);
            if (lock != NULL && lock->owner_thread != 0 && lock->owner_thread != thread->thread_id) {
                // Follow the chain to see if we get back to the original thread
                pid_t current_owner = lock->owner_thread;
                int steps = 0;
                const int max_steps = thread_count + 1;

                while (steps < max_steps) {
                    if (current_owner == thread->thread_id) {
                        verbose_print("Cycle detected: thread %d -> ... -> thread %d\n",
                                    thread->thread_id, current_owner);
                        return true;
                    }

                    // Find what the current owner is waiting for
                    thread_info_t* owner_thread = find_thread(current_owner);
                    if (owner_thread == NULL || owner_thread->waiting_for_lock == NULL) {
                        break;
                    }

                    lock_info_t* next_lock = find_lock_info(owner_thread->waiting_for_lock);
                    if (next_lock == NULL || next_lock->owner_thread == 0) {
                        break;
                    }

                    current_owner = next_lock->owner_thread;
                    steps++;
                }
            }
        }
        thread = thread->next;
    }

    return false;
}

bool lock_tracker_init(void) {
    // Create the lock graph
    lock_graph = graph_create();
    if (lock_graph == NULL) {
        fprintf(stderr, "Failed to create lock graph\n");
        return false;
    }

    // Initialize global state
    threads = NULL;
    locks = NULL;
    global_acquisition_counter = 0;

    verbose_print("Lock tracker initialized\n");
    return true;
}

void lock_tracker_cleanup(void) {
    // Clean up the graph
    if (lock_graph != NULL) {
        graph_destroy(lock_graph);
        lock_graph = NULL;
    }

    // Clean up thread information
    thread_info_t* thread = threads;
    while (thread != NULL) {
        thread_info_t* next_thread = thread->next;

        // Free held locks
        held_lock_t* lock = thread->held_locks;
        while (lock != NULL) {
            held_lock_t* next_lock = lock->next;
            free(lock);
            lock = next_lock;
        }

        free(thread);
        thread = next_thread;
    }
    threads = NULL;

    // Clean up lock information
    lock_info_t* lock = locks;
    while (lock != NULL) {
        lock_info_t* next_lock = lock->next;
        free(lock);
        lock = next_lock;
    }
    locks = NULL;

    verbose_print("Lock tracker cleaned up\n");
}

bool lock_tracker_register_thread(pid_t thread_id) {
    // Check if the thread is already registered
    if (find_thread(thread_id) != NULL) {
        verbose_print("Thread %d already registered\n", thread_id);
        return true;
    }

    // Create a new thread info structure
    thread_info_t* thread = malloc(sizeof(thread_info_t));
    if (thread == NULL) {
        fprintf(stderr, "Failed to allocate memory for thread info\n");
        return false;
    }

    thread->thread_id = thread_id;
    thread->held_locks = NULL;
    thread->lock_count = 0;
    thread->total_acquisitions = 0;
    thread->last_activity = time(NULL);
    thread->waiting_for_lock = NULL;
    thread->is_blocked = false;
    thread->next = threads;
    threads = thread;

    verbose_print("Registered thread %d\n", thread_id);
    return true;
}

void lock_tracker_unregister_thread(pid_t thread_id) {
    thread_info_t** thread_ptr = &threads;
    thread_info_t* thread;

    // Find the thread in our list
    while (*thread_ptr != NULL) {
        thread = *thread_ptr;

        if (thread->thread_id == thread_id) {
            // Remove the thread from the list
            *thread_ptr = thread->next;

            // Free held locks
            held_lock_t* lock = thread->held_locks;
            while (lock != NULL) {
                held_lock_t* next_lock = lock->next;
                free(lock);
                lock = next_lock;
            }

            free(thread);
            verbose_print("Unregistered thread %d\n", thread_id);
            return;
        }

        thread_ptr = &(thread->next);
    }

    verbose_print("Thread %d not found for unregistration\n", thread_id);
}

bool lock_tracker_register_acquisition(pid_t thread_id, void* lock_addr, bool is_recursive) {
    // Find or create the thread info
    thread_info_t* thread = find_thread(thread_id);
    if (thread == NULL) {
        if (!lock_tracker_register_thread(thread_id)) {
            return false;
        }
        thread = find_thread(thread_id);
    }

    // Update thread activity
    thread->last_activity = time(NULL);
    thread->waiting_for_lock = NULL; // No longer waiting since we're acquiring
    thread->is_blocked = false;

    // Find or create lock info
    lock_info_t* lock_info = find_or_create_lock_info(lock_addr);
    if (lock_info == NULL) {
        fprintf(stderr, "Failed to create lock info for %p\n", lock_addr);
        return false;
    }

    // Check for recursive acquisition
    held_lock_t* existing_lock = thread_find_held_lock(thread, lock_addr);
    if (existing_lock != NULL) {
        if (is_recursive) {
            existing_lock->recursion_count++;
            verbose_print("Thread %d recursively acquiring lock %p (count: %d)\n",
                         thread_id, lock_addr, existing_lock->recursion_count);
            return true;
        } else {
            verbose_print("Warning: Thread %d attempting non-recursive acquisition of already held lock %p\n",
                         thread_id, lock_addr);
            return false;
        }
    }

    // Check if lock is already owned by another thread
    if (lock_info->owner_thread != 0 && lock_info->owner_thread != thread_id) {
        lock_info->contention_count++;
        lock_info->is_contended = true;
        verbose_print("Lock %p is contended (owned by %d, requested by %d)\n",
                     lock_addr, lock_info->owner_thread, thread_id);

        // Mark this thread as waiting
        thread->waiting_for_lock = lock_addr;
        thread->is_blocked = true;

        // Check for potential deadlock using wait-for graph
        if (detect_wait_for_cycle()) {
            fprintf(stderr, "DEADLOCK DETECTED: Circular wait condition found!\n");
            fprintf(stderr, "Thread %d waiting for lock %p (owned by %d)\n",
                    thread_id, lock_addr, lock_info->owner_thread);
            return false;
        }

        // This would normally block, but in our simulation we proceed
        return true;
    }

    // Find or create the lock node for dependency graph
    graph_node_t* lock_node = graph_find_or_create_node(lock_graph, lock_addr);
    if (lock_node == NULL) {
        fprintf(stderr, "Failed to create node for lock %p\n", lock_addr);
        return false;
    }

    // Check lock ordering for potential deadlocks
    bool potential_deadlock = false;

    if (thread->lock_count > 0) {
        // For each lock already held by this thread
        held_lock_t* held_lock = thread->held_locks;
        while (held_lock != NULL) {
            graph_node_t* held_node = graph_find_or_create_node(lock_graph, held_lock->lock_addr);

            // Check if adding this dependency would create a cycle
            if (graph_would_create_cycle(lock_graph, held_node, lock_node)) {
                fprintf(stderr, "WARNING: Lock order violation detected!\n");
                fprintf(stderr, "Thread %d attempting to acquire lock %p while holding lock %p\n",
                        thread_id, lock_addr, held_lock->lock_addr);
                fprintf(stderr, "This violates a previously established lock ordering and may lead to deadlock.\n");

                potential_deadlock = true;
            } else {
                // Add the dependency: held_lock -> lock_addr
                graph_add_edge(lock_graph, held_node, lock_node);
                verbose_print("Added dependency: %p -> %p\n", held_lock->lock_addr, lock_addr);
            }

            held_lock = held_lock->next;
        }
    }

    // Add the lock to the thread's held locks
    held_lock_t* new_lock = malloc(sizeof(held_lock_t));
    if (new_lock == NULL) {
        fprintf(stderr, "Failed to allocate memory for held lock\n");
        return false;
    }

    new_lock->lock_addr = lock_addr;
    new_lock->acquisition_time = time(NULL);
    new_lock->acquisition_order = ++global_acquisition_counter;
    new_lock->is_recursive = is_recursive;
    new_lock->recursion_count = 1;
    new_lock->next = thread->held_locks;
    thread->held_locks = new_lock;
    thread->lock_count++;
    thread->total_acquisitions++;

    // Update lock info
    lock_info->owner_thread = thread_id;
    lock_info->last_acquisition = new_lock->acquisition_time;
    lock_info->is_contended = false;

    verbose_print("Thread %d acquired lock %p (total: %d, order: %d)\n",
                  thread_id, lock_addr, thread->lock_count, new_lock->acquisition_order);

    return !potential_deadlock;
}

void lock_tracker_register_release(pid_t thread_id, void* lock_addr) {
    // Find the thread info
    thread_info_t* thread = find_thread(thread_id);
    if (thread == NULL) {
        verbose_print("Thread %d not found for lock release\n", thread_id);
        return;
    }

    // Update thread activity
    thread->last_activity = time(NULL);

    // Find lock info
    lock_info_t* lock_info = find_lock_info(lock_addr);

    // Find and remove the lock from the thread's held locks
    held_lock_t** lock_ptr = &(thread->held_locks);
    held_lock_t* lock;

    while (*lock_ptr != NULL) {
        lock = *lock_ptr;

        if (lock->lock_addr == lock_addr) {
            // Handle recursive locks
            if (lock->is_recursive && lock->recursion_count > 1) {
                lock->recursion_count--;
                verbose_print("Thread %d recursively released lock %p (count: %d)\n",
                             thread_id, lock_addr, lock->recursion_count);
                return;
            }

            // Remove the lock from the list
            *lock_ptr = lock->next;
            free(lock);
            thread->lock_count--;

            // Update lock info
            if (lock_info != NULL) {
                lock_info->owner_thread = 0;
                lock_info->is_contended = false;
            }

            verbose_print("Thread %d released lock %p (remaining: %d)\n",
                         thread_id, lock_addr, thread->lock_count);
            return;
        }

        lock_ptr = &(lock->next);
    }

    verbose_print("Warning: Thread %d releasing lock %p that it doesn't hold\n",
                  thread_id, lock_addr);
}

bool lock_tracker_check_deadlocks(void) {
    if (lock_graph == NULL) {
        return false;
    }

    // Check for cycles in the lock dependency graph
    bool has_cycle = graph_has_cycle(lock_graph);

    // Also check for wait-for cycles
    bool has_wait_cycle = detect_wait_for_cycle();

    // Check for potential deadlocks based on blocked threads
    bool has_blocked_deadlock = false;
    int blocked_thread_count = 0;

    thread_info_t* thread = threads;
    while (thread != NULL) {
        if (thread->is_blocked && thread->waiting_for_lock != NULL) {
            blocked_thread_count++;
        }
        thread = thread->next;
    }

    // If we have multiple blocked threads, it might be a deadlock
    if (blocked_thread_count >= 2) {
        has_blocked_deadlock = true;
        verbose_print("Potential deadlock: %d threads are blocked\n", blocked_thread_count);
    }

    bool deadlock_detected = has_cycle || has_wait_cycle || has_blocked_deadlock;

    if (deadlock_detected) {
        fprintf(stderr, "DEADLOCK DETECTED!\n");
        if (has_cycle) {
            fprintf(stderr, "- Circular lock dependencies found in acquisition graph\n");
        }
        if (has_wait_cycle) {
            fprintf(stderr, "- Circular wait condition detected\n");
        }
        if (has_blocked_deadlock) {
            fprintf(stderr, "- Multiple threads blocked on lock operations\n");
        }

        lock_tracker_print_graph();
        lock_tracker_print_thread_locks();
        lock_tracker_print_lock_states();
    }

    return deadlock_detected;
}

void lock_tracker_print_graph(void) {
    if (lock_graph == NULL) {
        printf("Lock graph not initialized\n");
        return;
    }

    printf("\n=== Lock Dependency Graph ===\n");
    graph_print(lock_graph, format_ptr);
    printf("============================\n\n");
}

void lock_tracker_print_thread_locks(void) {
    printf("\n=== Thread Lock States ===\n");

    thread_info_t* thread = threads;
    while (thread != NULL) {
        printf("Thread %d holds %d locks: ", thread->thread_id, thread->lock_count);

        held_lock_t* lock = thread->held_locks;
        while (lock != NULL) {
            printf("%p ", lock->lock_addr);
            lock = lock->next;
        }
        printf("\n");

        thread = thread->next;
    }

    printf("========================\n\n");
}

size_t lock_tracker_get_lock_count(void) {
    if (lock_graph == NULL) {
        return 0;
    }

    return graph_node_count(lock_graph);
}

size_t lock_tracker_get_thread_count(void) {
    size_t count = 0;
    thread_info_t* thread = threads;

    while (thread != NULL) {
        count++;
        thread = thread->next;
    }

    return count;
}

void lock_tracker_print_lock_states(void) {
    printf("\n=== Lock States ===\n");

    lock_info_t* lock = locks;
    while (lock != NULL) {
        printf("Lock %p: ", lock->lock_addr);
        if (lock->owner_thread != 0) {
            printf("owned by thread %d", lock->owner_thread);
            if (lock->is_contended) {
                printf(" (CONTENDED, %d conflicts)", lock->contention_count);
            }
        } else {
            printf("free");
        }

        if (lock->last_acquisition > 0) {
            printf(" (last acquired: %s)", ctime(&lock->last_acquisition));
        } else {
            printf("\n");
        }

        lock = lock->next;
    }

    printf("===================\n\n");
}

void lock_tracker_set_verbose(bool enable) {
    verbose = enable;
}
