#include "raylib.h"
#include "game.h"
#include "assets.h"

#define FB_RATIO 5 // either 5 for less pixel clutter, 6 for pixelated look. All other values are too blocky or too "smooth"

#define screenWidth 1920
#define screenHeight 1080

#define renderWidth screenWidth/FB_RATIO
#define renderHeight screenHeight/FB_RATIO


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Lane Shooter");
    SetTargetFPS(60);
    ToggleFullscreen();
    SetWindowMonitor(2);

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