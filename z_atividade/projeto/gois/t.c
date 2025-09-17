#include "raylib.h"
#include <pthread.h>

void d() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("It works!", 350, 280, 20, BLACK);
        EndDrawing();
    }
}

void* whiless(void*){
    // d();
    return NULL;
}

int main() {
    InitWindow(800, 600, "Test Window");

    pthread_t pd;
    pthread_create(&pd, NULL, whiless,NULL);

    pthread_join(pd, NULL);
    d();
    CloseWindow();
    return 0;
}
