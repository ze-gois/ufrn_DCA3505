#include <asm-generic/errno.h>
#include "approach_1.h"
#include <stdlib.h>
#include <stdio.h>

graph_t *wait_graph = NULL;
mutex_info_t *mutex_list = NULL;
pthread_mutex_t meta_lock = PTHREAD_MUTEX_INITIALIZER;

// Find or create mutex_info
static mutex_info_t* get_mutex_info(pthread_mutex_t *m) {
    real_lock(&meta_lock);  // Protect
    mutex_info_t *info = mutex_list;
    while (info) {
        if (info->mutex == m) {
            real_unlock(&meta_lock);
            return info;
        }
        info = info->next;
    }
    // Create new
    info = malloc(sizeof(mutex_info_t));
    if (!info) {
        real_unlock(&meta_lock);
        return NULL;
    }
    info->mutex = m;
    info->owner = 0;
    info->is_recursive = false;
    info->waiters = NULL;
    info->next = mutex_list;
    mutex_list = info;
    real_unlock(&meta_lock);
    return info;
}

// Add waiter to queue
static void add_waiter(mutex_info_t *info, pthread_t tid) {
    waiter_t *w = malloc(sizeof(waiter_t));
    if (!w) return;
    w->tid = tid;
    w->next = info->waiters;
    info->waiters = w;
}

// Remove specific waiter
static void remove_waiter(mutex_info_t *info, pthread_t tid) {
    waiter_t *prev = NULL, *curr = info->waiters;
    while (curr) {
        if (curr->tid == tid) {
            if (prev) prev->next = curr->next;
            else info->waiters = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void init(void) {
    wait_graph = graph_create();
}

void destroy(void) {
    // Cleanup mutex_list and waiters
    mutex_info_t *minfo = mutex_list;
    while (minfo) {
        mutex_info_t *next_m = minfo->next;
        waiter_t *w = minfo->waiters;
        while (w) {
            waiter_t *next_w = w->next;
            free(w);
            w = next_w;
        }
        free(minfo);
        minfo = next_m;
    }
    graph_destroy(wait_graph);
}

void pml_pre(pthread_mutex_t *mutex) {
    pthread_t self = pthread_self();
    mutex_info_t *info = get_mutex_info(mutex);
    if (!info) return;

    real_lock(&meta_lock);
    if (info->owner == self) {
        if (info->is_recursive) {
            // Allow recursive lock, no waiter/edge added
            real_unlock(&meta_lock);
            return;
        } else {
            // Non-recursive self-lock: deadlock
            printf("Self-deadlock detected: attempting to relock non-recursive mutex.\n");
            // Model as self-loop in graph for cycle detection
            graph_node_t *node_self = graph_find_or_create_node(wait_graph, (void*)self);
            // Add self-loop (waiter -> owner, which is self -> self)
            graph_add_edge(wait_graph, node_self, node_self);
            // Now check for cycle (will detect the self-loop)
            if (graph_has_cycle(wait_graph)) {
                printf("Cycle detected in wait graph (self-loop).\n");
                exit(EDEADLOCK);
                // Optional: graph_visualize(wait_graph, print_thread_func); abort();
            }
            // Note: Real lock will still hang; this is just detection
            real_unlock(&meta_lock);
            return;
        }
    }
    if (info->owner != 0) {
        // Locked by other: add waiter and edge
        add_waiter(info, self);
        graph_node_t *node_self = graph_find_or_create_node(wait_graph, (void*)self);
        graph_node_t *node_owner = graph_find_or_create_node(wait_graph, (void*)info->owner);
        if (graph_would_create_cycle(wait_graph, node_self, node_owner)) {
            printf("Deadlock detected!\n");
            exit(EDEADLOCK);
            // Optional: graph_visualize(wait_graph, print_thread_func); abort();
        }
        graph_add_edge(wait_graph, node_self, node_owner);
    }
    real_unlock(&meta_lock);
}

int pml_pos(pthread_mutex_t *mutex, int ret) {
    if (ret != 0) return ret;  // Error (e.g., EDEADLK for error-check mutex), no update
    pthread_t self = pthread_self();
    mutex_info_t *info = get_mutex_info(mutex);
    if (!info) return ret;

    real_lock(&meta_lock);
    pthread_t prev_owner = info->owner;
    info->owner = self;
    remove_waiter(info, self);  // Remove self if was waiting
    // Remove outgoing edge from self (if any)
    graph_node_t *node_self = graph_find_node(wait_graph, (void*)self);
    graph_node_t *node_prev = graph_find_node(wait_graph, (void*)prev_owner);
    if (node_self && node_prev) {
        graph_remove_edge(wait_graph, node_self, node_prev);
    }
    // Update remaining waiters' edges to new owner
    waiter_t *w = info->waiters;
    while (w) {
        graph_node_t *node_w = graph_find_node(wait_graph, (void*)w->tid);
        if (node_w && node_prev) {
            graph_remove_edge(wait_graph, node_w, node_prev);
        }
        graph_node_t *node_new = graph_find_node(wait_graph, (void*)self);
        if (node_w && node_new) {
            graph_add_edge(wait_graph, node_w, node_new);
        }
        w = w->next;
    }
    real_unlock(&meta_lock);
    return ret;
}

void pmu_pre(pthread_mutex_t *mutex) {
    // Minimal: Could add owner check here if needed
}

int pmu_pos(pthread_mutex_t *mutex, int ret) {
    if (ret != 0) return ret;
    pthread_t self = pthread_self();
    mutex_info_t *info = get_mutex_info(mutex);
    if (!info || info->owner != self) return ret;

    real_lock(&meta_lock);
    // Remove edges to self from this mutex's waiters
    waiter_t *w = info->waiters;
    while (w) {
        graph_node_t *node_w = graph_find_node(wait_graph, (void*)w->tid);
        graph_node_t *node_self = graph_find_node(wait_graph, (void*)self);
        if (node_w && node_self) {
            graph_remove_edge(wait_graph, node_w, node_self);
        }
        w = w->next;
    }
    info->owner = 0;
    // Waiters stay (system will wake them sequentially)
    real_unlock(&meta_lock);
    return ret;
}

void pmi_pre(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
    // Minimal pre-init logic
}

int pmi_pos(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr, int ret) {
    if (ret != 0) return ret;
    mutex_info_t *info = get_mutex_info(mutex);
    if (!info) return ret;

    real_lock(&meta_lock);
    int type = PTHREAD_MUTEX_DEFAULT;  // Fallback
    if (attr) {
        pthread_mutexattr_gettype(attr, &type);
    }
    info->is_recursive = (type == PTHREAD_MUTEX_RECURSIVE);
    real_unlock(&meta_lock);
    return ret;
}

void pmd_pre(pthread_mutex_t *mutex) {
    // Minimal pre-destroy logic
}

int pmd_pos(pthread_mutex_t *mutex, int ret) {
    if (ret != 0) return ret;
    real_lock(&meta_lock);
    mutex_info_t *prev = NULL, *curr = mutex_list;
    while (curr) {
        if (curr->mutex == mutex) {
            if (prev) prev->next = curr->next;
            else mutex_list = curr->next;
            // Free waiters
            waiter_t *w = curr->waiters;
            while (w) {
                waiter_t *next_w = w->next;
                free(w);
                w = next_w;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    real_unlock(&meta_lock);
    return ret;
}
