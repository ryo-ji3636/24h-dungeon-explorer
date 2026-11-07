#include "raylib.h"

int main() {
    InitWindow(800, 600, "raylib Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangle(300, 200, 200, 100, BLUE);
        DrawText("raylib works!", 310, 320, 25, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}