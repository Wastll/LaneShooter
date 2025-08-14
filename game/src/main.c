#include "raylib.h"

int main(void)
{
    // Screen dimensions
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Initialize the window
    InitWindow(screenWidth, screenHeight, "Lane Shooter - Main Game");

    // Target FPS (optional)
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // ...

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Lane Shooter - Main Game Placeholder", 20, 20, 20, DARKGRAY);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}
