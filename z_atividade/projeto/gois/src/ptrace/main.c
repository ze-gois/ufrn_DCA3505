/**
 * @file main.c
 * @brief Main program for ptrace-based deadlock detection
 *
 * This file implements a command-line utility that uses ptrace to monitor
 * a target process, track its mutex operations, and detect potential deadlocks.
 */

#include "ptrace_attach.h"
#include "syscall_intercept.h"
#include "pthread_structures.h"
#include "lock_tracker.h"
#include "backtrace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// Program configuration
typedef struct {
    pid_t target_pid;
    int timeout_seconds;
    bool monitor_all_threads;
    bool detect_only;
    int analysis_interval;
    bool verbose;
    bool analyze_only;
    bool continuous_mode;
    const char* output_file;
} config_t;

// Global state
static volatile sig_atomic_t exit_requested = 0;
static config_t config = {0};
static FILE* output_stream = NULL;

// Signal handler for graceful termination
static void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        fprintf(stderr, "\nReceived signal %d, shutting down gracefully...\n", sig);
        exit_requested = 1;
    }
}

// Print usage information
static void print_usage(const char* program_name) {
    printf("ptrace-lockdep - Advanced deadlock detection using ptrace\n\n");
    printf("Usage: %s [OPTIONS] PID\n\n", program_name);
    printf("Options:\n");
    printf("  -h, --help              Show this help message\n");
    printf("  -v, --verbose           Enable verbose output\n");
    printf("  -a, --all-threads       Monitor all threads (default: main thread only)\n");
    printf("  -t, --timeout=SECS      Set monitoring timeout in seconds (0 = no timeout)\n");
    printf("  -d, --detect-only       Only detect deadlocks, don't exit on detection\n");
    printf("  -i, --interval=SECS     Analysis interval in seconds (default: 1)\n");
    printf("  -e, --existing-only     Only analyze existing deadlocks, then exit\n");
    printf("  -c, --continuous        Continuous monitoring mode\n");
    printf("  -o, --output=FILE       Write results to file instead of stdout\n");
    printf("\nExamples:\n");
    printf("  %s 12345                    # Analyze process 12345 once\n", program_name);
    printf("  %s -a -c -t 60 12345        # Monitor all threads for 60 seconds\n", program_name);
    printf("  %s -e 12345                 # Check for existing deadlocks only\n", program_name);
}

// Parse command line arguments
static bool parse_arguments(int argc, char* argv[]) {
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"all-threads", no_argument, NULL, 'a'},
        {"timeout", required_argument, NULL, 't'},
        {"detect-only", no_argument, NULL, 'd'},
        {"interval", required_argument, NULL, 'i'},
        {"existing-only", no_argument, NULL, 'e'},
        {"continuous", no_argument, NULL, 'c'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    // Set defaults
    config.target_pid = -1;
    config.timeout_seconds = 0;
    config.monitor_all_threads = false;
    config.detect_only = false;
    config.analysis_interval = 1;
    config.verbose = false;
    config.analyze_only = false;
    config.continuous_mode = false;
    config.output_file = NULL;

    int opt;
    while ((opt = getopt_long(argc, argv, "hvat:di:eco:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);
            case 'v':
                config.verbose = true;
                break;
            case 'a':
                config.monitor_all_threads = true;
                break;
            case 't':
                config.timeout_seconds = atoi(optarg);
                if (config.timeout_seconds < 0) {
                    fprintf(stderr, "Error: Invalid timeout value: %s\n", optarg);
                    return false;
                }
                break;
            case 'd':
                config.detect_only = true;
                break;
            case 'i':
                config.analysis_interval = atoi(optarg);
                if (config.analysis_interval <= 0) {
                    fprintf(stderr, "Error: Invalid interval value: %s\n", optarg);
                    return false;
                }
                break;
            case 'e':
                config.analyze_only = true;
                break;
            case 'c':
                config.continuous_mode = true;
                break;
            case 'o':
                config.output_file = optarg;
                break;
            default:
                print_usage(argv[0]);
                return false;
        }
    }

    // Check if we have a PID argument
    if (optind >= argc) {
        fprintf(stderr, "Error: Missing PID argument\n");
        print_usage(argv[0]);
        return false;
    }

    // Parse PID
    config.target_pid = atoi(argv[optind]);
    if (config.target_pid <= 0) {
        fprintf(stderr, "Error: Invalid PID: %s\n", argv[optind]);
        return false;
    }

    // Validate argument combinations
    if (config.analyze_only && config.continuous_mode) {
        fprintf(stderr, "Error: Cannot use --existing-only with --continuous\n");
        return false;
    }

    return true;
}

// Initialize output stream
static bool initialize_output(void) {
    if (config.output_file) {
        output_stream = fopen(config.output_file, "w");
        if (!output_stream) {
            fprintf(stderr, "Error: Cannot open output file '%s': %s\n", 
                    config.output_file, strerror(errno));
            return false;
        }
    } else {
        output_stream = stdout;
    }
    return true;
}

// Initialize all subsystems
static bool initialize_subsystems(void) {
    // Set verbosity for all components
    syscall_set_verbose(config.verbose);
    lock_tracker_set_verbose(config.verbose);

    // Initialize lock tracker
    if (!lock_tracker_init()) {
        fprintf(stderr, "Error: Failed to initialize lock tracker\n");
        return false;
    }

    // Set backtrace options
    backtrace_set_use_debug_symbols(config.verbose);

    // Initialize syscall interception
    if (!syscall_intercept_init()) {
        fprintf(stderr, "Error: Failed to initialize syscall interception\n");
        lock_tracker_cleanup();
        return false;
    }

    // Initialize pthread structures
    if (!pthread_structures_init()) {
        fprintf(stderr, "Error: Failed to initialize pthread structures\n");
        syscall_intercept_cleanup();
        lock_tracker_cleanup();
        return false;
    }

    // Initialize backtrace subsystem
    if (!backtrace_init()) {
        fprintf(stderr, "Error: Failed to initialize backtrace subsystem\n");
        pthread_structures_cleanup();
        syscall_intercept_cleanup();
        lock_tracker_cleanup();
        return false;
    }

    return true;
}

// Clean up all subsystems
static void cleanup_subsystems(void) {
    backtrace_cleanup();
    pthread_structures_cleanup();
    syscall_intercept_cleanup();
    lock_tracker_cleanup();
}

// Check if target process exists and is accessible
static bool validate_target_process(void) {
    char proc_path[64];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/status", config.target_pid);
    
    if (access(proc_path, R_OK) != 0) {
        fprintf(stderr, "Error: Cannot access process %d: %s\n", 
                config.target_pid, strerror(errno));
        return false;
    }
    
    return true;
}

// Analyze process for existing deadlocks
static bool analyze_existing_deadlocks(void) {
    fprintf(output_stream, "Analyzing process %d for existing deadlocks...\n", config.target_pid);
    
    // For now, just do a basic check without complex backtrace analysis
    // TODO: Implement safer backtrace capture
    fprintf(output_stream, "Basic deadlock analysis - checking lock tracker state...\n");
    
    // Check if we can detect any obvious deadlock patterns
    bool deadlock_found = lock_tracker_check_deadlocks();
    
    if (deadlock_found) {
        fprintf(output_stream, "\n*** POTENTIAL DEADLOCK DETECTED ***\n");
        fprintf(output_stream, "Process %d may be in a deadlock state!\n", config.target_pid);
        return true;
    } else {
        fprintf(output_stream, "No obvious deadlocks detected in current state\n");
        return false;
    }
}

// Main monitoring loop
static bool monitor_process(void) {
    time_t start_time = time(NULL);
    bool deadlock_detected = false;

    fprintf(output_stream, "Starting monitoring of process %d\n", config.target_pid);
    if (config.monitor_all_threads) {
        fprintf(output_stream, "Monitoring all threads\n");
    }
    if (config.timeout_seconds > 0) {
        fprintf(output_stream, "Will monitor for %d seconds\n", config.timeout_seconds);
    }

    // Register the main thread with the lock tracker
    lock_tracker_register_thread(config.target_pid);

    // Attach to additional threads if requested
    if (config.monitor_all_threads) {
        int attached = ptrace_attach_all_threads(config.target_pid);
        if (attached == -1) {
            fprintf(stderr, "Warning: Failed to attach to all threads\n");
        } else {
            fprintf(output_stream, "Attached to %d threads\n", attached);
        }
    }

    // Main monitoring loop
    while (!exit_requested) {
        // Check timeout if specified
        if (config.timeout_seconds > 0) {
            time_t elapsed = time(NULL) - start_time;
            if (elapsed >= config.timeout_seconds) {
                fprintf(output_stream, "Timeout reached (%d seconds)\n", config.timeout_seconds);
                break;
            }
        }

        // Wait for the next system call
        bool entering;
        long syscall = ptrace_wait_for_syscall(config.target_pid, &entering);

        if (syscall == -1) {
            if (errno == ESRCH) {
                fprintf(output_stream, "Process %d has terminated\n", config.target_pid);
            } else {
                fprintf(stderr, "Lost connection to process %d: %s\n", 
                        config.target_pid, strerror(errno));
            }
            break;
        }

        // Process the system call
        if (syscall_process(config.target_pid, syscall, entering)) {
            // Check for deadlocks periodically
            static time_t last_check = 0;
            time_t now = time(NULL);
            
            if (now - last_check >= config.analysis_interval) {
                if (lock_tracker_check_deadlocks()) {
                    fprintf(output_stream, "\n*** DEADLOCK DETECTED ***\n");
                    fprintf(output_stream, "Time: %s", ctime(&now));
                    
                    // Print lock graph state
                    FILE* old_stdout = stdout;
                    if (output_stream != stdout) {
                        stdout = output_stream;
                    }
                    lock_tracker_print_graph();
                    lock_tracker_print_thread_locks();
                    if (output_stream != stdout) {
                        stdout = old_stdout;
                    }

                    deadlock_detected = true;
                    
                    if (!config.detect_only) {
                        fprintf(output_stream, "Exiting due to deadlock detection\n");
                        break;
                    }
                }
                last_check = now;
            }
        }
    }

    return deadlock_detected;
}

// Print summary statistics
static void print_summary(bool deadlock_found) {
    fprintf(output_stream, "\n=== Summary ===\n");
    fprintf(output_stream, "Target process: %d\n", config.target_pid);
    fprintf(output_stream, "Locks tracked: %zu\n", lock_tracker_get_lock_count());
    fprintf(output_stream, "Threads tracked: %zu\n", lock_tracker_get_thread_count());
    fprintf(output_stream, "Deadlock detected: %s\n", deadlock_found ? "YES" : "NO");
    fprintf(output_stream, "===============\n");
}

int main(int argc, char* argv[]) {
    int exit_code = EXIT_SUCCESS;
    bool deadlock_found = false;

    // Parse command line arguments
    if (!parse_arguments(argc, argv)) {
        return EXIT_FAILURE;
    }

    // Initialize output stream
    if (!initialize_output()) {
        return EXIT_FAILURE;
    }

    // Validate target process
    if (!validate_target_process()) {
        if (output_stream != stdout) fclose(output_stream);
        return EXIT_FAILURE;
    }

    // Set up signal handlers for graceful termination
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    
    if (sigaction(SIGINT, &sa, NULL) != 0 || sigaction(SIGTERM, &sa, NULL) != 0) {
        fprintf(stderr, "Warning: Failed to set up signal handlers\n");
    }

    // Initialize subsystems
    if (!initialize_subsystems()) {
        fprintf(stderr, "Initialization failed\n");
        if (output_stream != stdout) fclose(output_stream);
        return EXIT_FAILURE;
    }

    // Attach to the target process
    if (!ptrace_attach(config.target_pid)) {
        fprintf(stderr, "Failed to attach to process %d: %s\n", 
                config.target_pid, strerror(errno));
        cleanup_subsystems();
        if (output_stream != stdout) fclose(output_stream);
        return EXIT_FAILURE;
    }

    // Main execution flow
    if (config.analyze_only) {
        // Just analyze for existing deadlocks
        deadlock_found = analyze_existing_deadlocks();
        if (deadlock_found) {
            exit_code = EXIT_FAILURE;
        }
    } else {
        // Check for existing deadlocks first
        deadlock_found = analyze_existing_deadlocks();
        
        if (!deadlock_found && config.continuous_mode) {
            // Start continuous monitoring
            if (monitor_process()) {
                deadlock_found = true;
                exit_code = EXIT_FAILURE;
            }
        }
    }

    // Print summary
    print_summary(deadlock_found);

    // Clean up
    ptrace_detach(config.target_pid);
    cleanup_subsystems();
    
    if (output_stream != stdout) {
        fclose(output_stream);
    }

    if (config.verbose) {
        fprintf(stderr, "ptrace-lockdep completed with exit code %d\n", exit_code);
    }

    return exit_code;
}