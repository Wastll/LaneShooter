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

//     else
//     {
//         if (animations[player].tex.id != anim_walk.tex.id)
//         {
//             animations[player] = anim_walk;
//         }
//         direction_vec = Vector2Normalize((Vector2){accelerations[player].x, accelerations[player].z});

//         float angle = atan2f(direction_vec.y, direction_vec.x); // returns -pi to pi
//         if (angle < 0)
//             angle += 2 * PI;
//         cycle_index = (int)(angle / (PI / 4) + 6) % 8;
//         if (cycle_index > 4)
//             cycle_index = abs(cycle_index - 8);
//         printf("%f  %f\n", direction_vec.x, direction_vec.y);

//     }
//     movment_vec = Vector2Normalize((Vector2){accelerations[player].x, accelerations[player].z});

// }