#include "raylib.h"
#include "game.h"
#include "assets.h"

#define FB_RATIO 3

#define screenWidth 1920
#define screenHeight 1080

#define renderWidth screenWidth/FB_RATIO
#define renderHeight screenHeight/FB_RATIO


int main(void)
{
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Lane Shooter");
    init_game(renderWidth,renderHeight);
    SetWindowMonitor(2);
    ToggleFullscreen();
    SetTargetFPS(60);


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