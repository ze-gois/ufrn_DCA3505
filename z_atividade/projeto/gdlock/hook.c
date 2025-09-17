#include <pthread.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "hook.h"

real_mutex_lock_t real_lock = NULL;
real_mutex_unlock_t real_unlock = NULL;
real_mutex_init_t real_init = NULL;
real_mutex_destroy_t real_destroy = NULL;

void init_wrappers(void) {
    if (!real_lock) {
        real_lock = dlsym(RTLD_NEXT, "pthread_mutex_lock");
        real_unlock = dlsym(RTLD_NEXT, "pthread_mutex_unlock");
        real_init = dlsym(RTLD_NEXT, "pthread_mutex_init");
        real_destroy = dlsym(RTLD_NEXT, "pthread_mutex_destroy");
    }
}

__attribute__((constructor)) static void init_hook(void) {
    init_wrappers();
    init();
}

__attribute__((destructor)) static void dest_hook(void) {
    destroy();
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
    init_wrappers();
    pml_pre(mutex);
    int ret = real_lock(mutex);
    return pml_pos(mutex, ret);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    init_wrappers();
    pmu_pre(mutex);
    int ret = real_unlock(mutex);
    return pmu_pos(mutex, ret);
}

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
    init_wrappers();
    pmi_pre(mutex, attr);
    int ret = real_init(mutex, attr);
    return pmi_pos(mutex, attr, ret);
}

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
    init_wrappers();
    pmd_pre(mutex);
    int ret = real_destroy(mutex);
    return pmd_pos(mutex, ret);
}
