/**
 * @file graph.h
 * @brief Graph representation and algorithms for deadlock detection
 *
 * This header defines the interfaces for a directed graph library used
 * to represent lock dependencies and perform cycle detection for deadlock
 * analysis.
 */

// #ifndef GRAPH_H
// #define GRAPH_H
#pragma once

#ifdef __GNUC__
  #define GRAPH_API __attribute__((visibility("default")))
#else
  #define GRAPH_API
#endif

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Forward declarations of opaque types
 */
typedef struct graph graph_t;
typedef struct graph_node graph_node_t;
typedef struct graph_edge graph_edge_t;

/**
 * @brief Creates a new directed graph
 * @return Pointer to the newly created graph, or NULL on failure
 */
GRAPH_API graph_t* graph_create(void);

/**
 * @brief Destroys a graph and frees all associated memory
 * @param graph The graph to destroy
 */
GRAPH_API void graph_destroy(graph_t* graph);

/**
 * @brief Creates or retrieves a node in the graph with the given identifier
 * @param graph The graph to operate on
 * @param id Unique identifier for the node (typically a pointer to the lock)
 * @return Pointer to the node, or NULL on failure
 */
GRAPH_API graph_node_t* graph_find_or_create_node(graph_t* graph, void* id);

/**
 * @brief Adds a directed edge between two nodes
 * @param graph The graph to operate on
 * @param from Source node
 * @param to Destination node
 * @return true if the edge was successfully added, false on failure
 */
GRAPH_API bool graph_add_edge(graph_t* graph, graph_node_t* from, graph_node_t* to);

/**
 * @brief Checks if adding an edge would create a cycle in the graph
 * @param graph The graph to check
 * @param from Source node for the potential new edge
 * @param to Destination node for the potential new edge
 * @return true if adding the edge would create a cycle, false otherwise
 */
GRAPH_API bool graph_would_create_cycle(graph_t* graph, graph_node_t* from, graph_node_t* to);

/**
 * @brief Performs cycle detection on the entire graph
 * @param graph The graph to check
 * @return true if a cycle is found, false otherwise
 */
GRAPH_API bool graph_has_cycle(graph_t* graph);

/**
 * @brief Gets the number of nodes in the graph
 * @param graph The graph to query
 * @return Number of nodes
 */
GRAPH_API size_t graph_node_count(graph_t* graph);

/**
 * @brief Gets the number of edges in the graph
 * @param graph The graph to query
 * @return Number of edges
 */
GRAPH_API size_t graph_edge_count(graph_t* graph);

/**
 * @brief Gets starting edge
 */
GRAPH_API graph_edge_t * graph_edge_get_stone(graph_t* graph);


 /**
  * @brief Gets starting edge
  */
GRAPH_API graph_node_t * graph_edge_get_from(graph_edge_t* edge);
GRAPH_API graph_node_t * graph_edge_get_to(graph_edge_t* edge);

GRAPH_API graph_edge_t* graph_edge_next(graph_edge_t* edge);
/**
 * @brief Gets the identifier associated with a node
 * @param node The node to query
 * @return The node's identifier
 */
GRAPH_API void* graph_node_get_id(graph_node_t* node);
GRAPH_API size_t graph_node_get_index(graph_node_t* node);
GRAPH_API graph_node_t* graph_node_get_next(graph_node_t* node);
GRAPH_API graph_node_t* graph_node_get_stone(graph_t *graph);

/**
 * @brief Gets all nodes in the graph
 * @param graph The graph to query
 * @param count Output parameter that will be set to the number of nodes returned
 * @return Array of pointers to nodes (must be freed by the caller)
 */
GRAPH_API graph_node_t** graph_get_all_nodes(graph_t* graph, size_t* count);


/**
 * @brief Gets all outgoing edges from a node
 * @param graph The graph to query
 * @param node The source node
 * @param count Output parameter that will be set to the number of edges returned
 * @return Array of pointers to destination nodes (must be freed by the caller)
 */
GRAPH_API graph_node_t** graph_get_outgoing_edges(graph_t* graph, graph_node_t* node, size_t* count);

/**
 * @brief Prints a representation of the graph for debugging
 * @param graph The graph to print
 * @param print_node_func Function to convert node IDs to string representations
 */
GRAPH_API void graph_print(graph_t* graph, const char* (*print_node_func)(void*));

/**
 * @brief Removes a directed edge between two nodes if it exists
 * @param graph The graph to operate on
 * @param from Source node
 * @param to Destination node
 * @return true if the edge was found and removed, false otherwise
 */
GRAPH_API bool graph_remove_edge(graph_t* graph, graph_node_t* from, graph_node_t* to);

GRAPH_API graph_node_t* graph_find_node(graph_t*, void*);

// #endif /* GRAPH_H */
