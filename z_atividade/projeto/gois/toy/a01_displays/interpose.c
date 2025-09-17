#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "interpose.h"

graph_t *our_graph = NULL;

// Tipo da função __libc_start_main
typedef int (*libc_start_main_fn)(
    int (*main)(int, char**, char**),
    int argc, char** ubp_av,
    void (*init)(void), void (*fini)(void),
    void (*rtld_fini)(void), void* stack_end
);

static int (*real_main)(int, char**, char**);
static libc_start_main_fn orig_libc_start_main;

int wrapped_main(int argc, char** argv, char** envp) {
    printf("[interpose] before real main\n");
    int ret = real_main(argc, argv, envp);
    printf("[interpose] after real main\n");
    return ret;
}

__attribute__((constructor))
static void setup(void) {
    our_graph = graph_create();
    for (size_t s = 0; s < 10; s++){
        graph_node_t* from = graph_find_or_create_node(our_graph, (void *) (s%10));
        graph_node_t* to = graph_find_or_create_node(our_graph, (void *) ((s+1)%10));
        graph_add_edge(our_graph, from, to);
    }

    graph_visualize(our_graph, NULL);

    orig_libc_start_main = (libc_start_main_fn)dlsym(RTLD_NEXT, "__libc_start_main");
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
