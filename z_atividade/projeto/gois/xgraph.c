#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    graph_t* graph =  graph_create();

    for (size_t n = 0; n< 15; n++){
        graph_node_t *from = graph_find_or_create_node(graph, (void *) n);
        graph_node_t *to = graph_find_or_create_node(graph, (void *) ((n+1)%15));

        graph_add_edge(graph, from, to);
    }

    printf("\n>>>%zu\n",graph_edge_count(graph));

    graph_visualize(graph, NULL);
    graph_destroy(graph);
    return 0;
}
