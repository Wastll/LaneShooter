// world.c
#include "world.h"
#include "assets.h"

#define lane_w 64 // Lane length
#define lane_h 5  // Lane count

Color lane_depth_tint[lane_h];

void init_world(void)
{
    // Init depth shading color values
    int lane_depth_darkness_lvl = 18;
    for (int i = 0; i < lane_h; i++)
        lane_depth_tint[i] = (Color){255 - lane_depth_darkness_lvl * i, 255 - lane_depth_darkness_lvl * i, 255, 255};
}

void update_world(float dt)
{
}

// Background as part of the world for now
void draw_background(int fb_w, int fb_h)
{
    DrawTexturePro(
        get_assets()->skybox,
        (Rectangle){0, 0, get_assets()->skybox.width, get_assets()->skybox.height},
        (Rectangle){0, 0, fb_w, fb_h},
        (Vector2){0, 0}, 0, WHITE);
}

void draw_lanes(void)
{
    float cube_scale = 1.0f;

    for (int i = 0; i < lane_w; i++)
        for (int j = 0; j < lane_h; j++)
        {
            Vector3 cube_pos =
                (Vector3){
                    i * cube_scale + cube_scale / 2,
                    -cube_scale / 2,
                    -j * cube_scale - cube_scale / 2};

            DrawModel(get_assets()->cube, cube_pos, cube_scale, lane_depth_tint[j]);
        }
}
