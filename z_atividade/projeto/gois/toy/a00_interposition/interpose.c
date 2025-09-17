#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Tipo da função __libc_start_main
typedef int (*libc_start_main_fn)(
    int (*main)(int, char**, char**),
    int argc, char** ubp_av,
    void (*init)(void), void (*fini)(void),
    void (*rtld_fini)(void), void* stack_end
);

static int (*real_main)(int, char**, char**);
static libc_start_main_fn orig_libc_start_main;

static int (*real_pthread_mutex_lock)(pthread_mutex_t*) = NULL;
static int (*real_pthread_mutex_unlock)(pthread_mutex_t*) = NULL;
static int (*real_pthread_mutex_trylock)(pthread_mutex_t*) = NULL;

int wrapped_main(int argc, char** argv, char** envp) {
    printf("[interpose] before real main\n");
    int ret = real_main(argc, argv, envp);
    printf("[interpose] after real main\n");
    return ret;
}

__attribute__((constructor))
static void setup(void) {
    orig_libc_start_main = (libc_start_main_fn)dlsym(RTLD_NEXT, "__libc_start_main");

    real_pthread_mutex_lock = dlsym(RTLD_NEXT, "pthread_mutex_lock");
    real_pthread_mutex_unlock = dlsym(RTLD_NEXT, "pthread_mutex_unlock");
    real_pthread_mutex_trylock = dlsym(RTLD_NEXT, "pthread_mutex_trylock");

    if (!orig_libc_start_main) {
        fprintf(stderr, "Failed to find __libc_start_main\n");
        exit(1);
    }
}

int __libc_start_main(
    int (*main_fn)(int, char**, char**),
    int argc, char** ubp_av,
    void (*init)(void), void (*fini)(void),
    void (*rtld_fini)(void), void* stack_end
) {
    real_main = main_fn;

    printf("[interpose] before _start_main\n");

    int _start_main = orig_libc_start_main(
        wrapped_main, argc, ubp_av,
        init, fini, rtld_fini, stack_end
    );

    return _start_main;
}
