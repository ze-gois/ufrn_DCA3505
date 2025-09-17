#include <stdio.h>
#include <pthread.h>
#include "hook.h"
#include "graph.h"

// Waiter node for per-mutex queue
typedef struct waiter {
    pthread_t tid;
    struct waiter *next;
} waiter_t;

// Per-mutex info
typedef struct mutex_info {
    pthread_mutex_t *mutex;
    pthread_t owner;
    bool is_recursive;
    waiter_t *waiters;
    struct mutex_info *next;
} mutex_info_t;

// Globals (defined in approach_1.c)
extern graph_t *wait_graph;
extern mutex_info_t *mutex_list;
extern pthread_mutex_t meta_lock;

extern real_mutex_lock_t real_lock;
extern real_mutex_unlock_t real_unlock;
extern real_mutex_init_t real_init;
extern real_mutex_destroy_t real_destroy;
