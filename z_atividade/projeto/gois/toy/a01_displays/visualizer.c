#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "graph.h"

/**
 * Utility function to draw an arrow from start to end
 */
static void DrawArrow(Vector2 start, Vector2 end, Color color) {
    DrawLineV(start, end, color);

    Vector2 dir = {end.x - start.x, end.y - start.y};
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.0f) {
        dir.x /= len;
        dir.y /= len;
    }

    Vector2 perp = {-dir.y, dir.x};

    Vector2 arrow1 = {end.x - 10.0f * dir.x + 5.0f * perp.x, end.y - 10.0f * dir.y + 5.0f * perp.y};
    Vector2 arrow2 = {end.x - 10.0f * dir.x - 5.0f * perp.x, end.y - 10.0f * dir.y - 5.0f * perp.y};

    DrawLineV(end, arrow1, color);
    DrawLineV(end, arrow2, color);
}

/**
 * Visualizes the graph in a 2D window using raylib
 */
void graph_visualize(graph_t* graph, const char* (*print_node_func)(void*)) {
    if (graph == NULL || graph_node_count(graph) == 0) {
        return;
    }

    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Graph Visualization");
    SetTargetFPS(60);

    // Allocate positions array indexed by node->index
    Vector2* positions = malloc(graph_node_count(graph) * sizeof(Vector2));
    if (positions == NULL) {
        CloseWindow();
        return;
    }

    // Compute positions in a circle layout
    float circleRadius = fminf((float)screenWidth, (float)screenHeight) / 2.0f - 50.0f;
    float centerX = (float)screenWidth / 2.0f;
    float centerY = (float)screenHeight / 2.0f;

    for (size_t i = 0; i < graph_node_count(graph); i++) {
        float angle = (2.0f * PI * (float)i) / (float)graph_node_count(graph);
        positions[i].x = centerX + circleRadius * cosf(angle);
        positions[i].y = centerY + circleRadius * sinf(angle);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw edges as arrows
        graph_edge_t* edge = graph_edge_get_stone(graph);
        while (edge) {
            graph_node_t* from = graph_edge_get_from(edge);
            graph_node_t* to = graph_edge_get_to(edge);

            size_t from_idx = graph_node_get_index(from);
            size_t to_idx = graph_node_get_index(to);

            Vector2 start = positions[from_idx];
            Vector2 end = positions[to_idx];
            DrawArrow(start, end, BLACK);
            edge = graph_edge_next(edge);
        }

        // Draw nodes
        graph_node_t* node = graph_node_get_stone(graph);
        while (node) {
            size_t idx = graph_node_get_index(node);
            void* id = graph_node_get_id(node);
            Vector2 pos = positions[idx];
            DrawCircleV(pos, 20.0f, BLUE);

            const char* label;
            if (print_node_func) {
                label = print_node_func(id);
            } else {
                label = TextFormat("%zu", idx);
            }
            DrawText(label ? label : "?", (int)pos.x - 10, (int)pos.y - 10, 20, BLACK);

            node = graph_node_get_next(node);
        }

        EndDrawing();
    }

    free(positions);
    CloseWindow();
}
