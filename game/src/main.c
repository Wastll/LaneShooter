#include "raylib.h"
#include "game.h"
#include "assets.h"

#define renderWidth 320
#define renderHeight 180

#define screenWidth 1920
#define screenHeight 1080

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Lane Shooter");
    SetTargetFPS(60);
    ToggleFullscreen();
    SetWindowMonitor(1);

    init_game(renderWidth,renderHeight);

    while (!WindowShouldClose())
    {
        draw_framebuffer();
        draw_upscale();
        update_game();
    }

    unload_assets();
    CloseWindow();
    return 0;
}
