/**
 * @file test_program.c
 * @brief Simple test program with mutex operations for testing ptrace-lockdep
 * 
 * This program creates multiple threads that acquire mutexes in different orders,
 * potentially creating deadlock situations for testing the ptrace-based detector.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>

// Global mutexes for testing
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Control variables
static volatile int running = 1;
static int test_mode = 0;

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        printf("\nReceived signal %d, shutting down...\n", sig);
        running = 0;
    }
}

// Thread 1: Acquires mutex1 then mutex2
void* thread1_func(void* arg) {
    (void)arg;
    printf("Thread 1 starting...\n");
    
    while (running) {
        printf("Thread 1: Acquiring mutex1...\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread 1: Got mutex1, working...\n");
        
        sleep(1); // Simulate work
        
        if (test_mode == 1) {
            printf("Thread 1: Acquiring mutex2...\n");
            pthread_mutex_lock(&mutex2);
            printf("Thread 1: Got mutex2, working...\n");
            
            sleep(1); // Simulate work
            
            pthread_mutex_unlock(&mutex2);
            printf("Thread 1: Released mutex2\n");
        }
        
        pthread_mutex_unlock(&mutex1);
        printf("Thread 1: Released mutex1\n");
        
        sleep(2); // Wait before next iteration
    }
    
    printf("Thread 1 exiting...\n");
    return NULL;
}

// Thread 2: Acquires mutex2 then mutex1 (potential deadlock with thread1)
void* thread2_func(void* arg) {
    (void)arg;
    printf("Thread 2 starting...\n");
    
    while (running) {
        printf("Thread 2: Acquiring mutex2...\n");
        pthread_mutex_lock(&mutex2);
        printf("Thread 2: Got mutex2, working...\n");
        
        sleep(1); // Simulate work
        
        if (test_mode == 1) {
            printf("Thread 2: Acquiring mutex1...\n");
            pthread_mutex_lock(&mutex1);
            printf("Thread 2: Got mutex1, working...\n");
            
            sleep(1); // Simulate work
            
            pthread_mutex_unlock(&mutex1);
            printf("Thread 2: Released mutex1\n");
        }
        
        pthread_mutex_unlock(&mutex2);
        printf("Thread 2: Released mutex2\n");
        
        sleep(2); // Wait before next iteration
    }
    
    printf("Thread 2 exiting...\n");
    return NULL;
}

// Thread 3: Uses mutex3 independently
void* thread3_func(void* arg) {
    (void)arg;
    printf("Thread 3 starting...\n");
    
    while (running) {
        printf("Thread 3: Acquiring mutex3...\n");
        pthread_mutex_lock(&mutex3);
        printf("Thread 3: Got mutex3, working...\n");
        
        sleep(2); // Simulate longer work
        
        pthread_mutex_unlock(&mutex3);
        printf("Thread 3: Released mutex3\n");
        
        sleep(1); // Wait before next iteration
    }
    
    printf("Thread 3 exiting...\n");
    return NULL;
}

// Function that creates a simple deadlock
void create_deadlock(void) {
    printf("\n=== CREATING DEADLOCK SCENARIO ===\n");
    
    pthread_t t1, t2;
    
    // Create two threads that will deadlock
    pthread_create(&t1, NULL, thread1_func, NULL);
    sleep(1); // Let thread1 start first
    pthread_create(&t2, NULL, thread2_func, NULL);
    
    // Wait for deadlock to occur
    printf("Waiting for potential deadlock...\n");
    sleep(10);
    
    printf("Attempting to join threads (may hang if deadlocked)...\n");
    pthread_cancel(t1);
    pthread_cancel(t2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

void print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("Options:\n");
    printf("  -h, --help       Show this help message\n");
    printf("  -d, --deadlock   Create a deadlock scenario\n");
    printf("  -s, --safe       Run in safe mode (no deadlock)\n");
    printf("  -t, --time=SECS  Run for specified seconds (default: infinite)\n");
    printf("  -v, --verbose    Enable verbose output\n");
    printf("\nThis program is designed to test ptrace-based deadlock detection.\n");
    printf("Use another terminal to run: ptrace-lockdep <PID>\n");
}

int main(int argc, char* argv[]) {
    int run_time = 0;
    int create_deadlock_scenario = 0;
    int verbose = 0;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--deadlock") == 0) {
            create_deadlock_scenario = 1;
            test_mode = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--safe") == 0) {
            test_mode = 0;
        } else if (strncmp(argv[i], "-t", 2) == 0 || strncmp(argv[i], "--time=", 7) == 0) {
            char* time_str = strchr(argv[i], '=');
            if (time_str) {
                run_time = atoi(time_str + 1);
            } else if (i + 1 < argc) {
                run_time = atoi(argv[++i]);
            }
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
    }
    
    printf("Test Program for ptrace-lockdep\n");
    printf("PID: %d\n", getpid());
    
    if (verbose) {
        printf("Test mode: %s\n", test_mode ? "Deadlock potential" : "Safe");
        printf("Run time: %s\n", run_time ? "Limited" : "Infinite");
    }
    
    // Set up signal handlers
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    
    if (create_deadlock_scenario) {
        create_deadlock();
        return 0;
    }
    
    // Create threads
    pthread_t threads[3];
    
    printf("Creating threads...\n");
    pthread_create(&threads[0], NULL, thread1_func, NULL);
    pthread_create(&threads[1], NULL, thread2_func, NULL);
    pthread_create(&threads[2], NULL, thread3_func, NULL);
    
    printf("Threads created. Use 'ptrace-lockdep %d' to monitor.\n", getpid());
    printf("Press Ctrl+C to stop.\n\n");
    
    // Main loop
    time_t start_time = time(NULL);
    while (running) {
        if (run_time > 0 && (time(NULL) - start_time) >= run_time) {
            printf("Time limit reached, shutting down...\n");
            break;
        }
        
        sleep(1);
        
        if (verbose && (time(NULL) - start_time) % 10 == 0) {
            printf("Running for %ld seconds...\n", time(NULL) - start_time);
        }
    }
    
    // Shutdown
    running = 0;
    printf("Waiting for threads to finish...\n");
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("All threads finished. Exiting.\n");
    return 0;
}