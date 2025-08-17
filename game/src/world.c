// world.c
#include "world.h"
#include "assets.h"

#define lane_w 64
#define lane_h 5

Color lane_depth_tint[lane_h];

void init_world(void)
{
    for (int i = 0; i < lane_h; i++)
    {
        const int lane_depth_darkness_lvl = 18;
        lane_depth_tint[i] = (Color){255 - lane_depth_darkness_lvl * i, 255 - lane_depth_darkness_lvl * i, 255, 255};
    }
}

void update_world(float dt)
{
}

// Background as part of the world for now
void draw_background(int fb_w, int fb_h){
    DrawTexturePro(
        get_assets()->skybox,
        (Rectangle){0, 0, (float)get_assets()->skybox.width, (float)get_assets()->skybox.height},
        (Rectangle){0, 0, fb_w, fb_h},
        (Vector2){0, 0}, 0.0f, WHITE);

}

void draw_lanes(void)
{
    GameAssets *assets = get_assets();
    for (int i = 0; i < lane_w; i++)
        for (int j = 0; j < lane_h; j++)
        {
            Vector3 pos1 = (Vector3){i * 16 + 0, 24, -j * 16};

            DrawModel(assets->cube, pos1, 16, WHITE);
        }
}
