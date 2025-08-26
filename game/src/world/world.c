// world.c
#include "world.h"
#include "assets.h"
#include "raymath.h"

Color lane_depth_tint[WORLD_LANES_H];

// Lanes / Ground as part of ECS

Entity e_lanes;
static void init_lanes(void)
{
    e_lanes = create_entity();
    add_position(e_lanes, (Vector3){0, 0, 0});
    hasBoundingBox[e_lanes]=true;
    bounding_boxes[e_lanes].min = (Vector3){0,-1,-WORLD_LANES_H};
    bounding_boxes[e_lanes].max = (Vector3){WORLD_LANES_W,0,0};
    hasCollision[e_lanes] = true;
}

static void update_lanes(void) {}

static void draw_lanes(void)
{
    float cube_scale = 1.0f;

    Vector3 cube_pos = positions[e_lanes];

    for (int i = 0; i < WORLD_LANES_W; i++)
        for (int j = 0; j < WORLD_LANES_H; j++)
        {
            cube_pos =
                (Vector3){
                    i * cube_scale + cube_scale / 2 + positions[e_lanes].x,
                    -cube_scale / 2 + positions[e_lanes].y,
                    -j * cube_scale - cube_scale / 2 + positions[e_lanes].z};

            DrawModel(get_assets()->cube_meadow, cube_pos, cube_scale, lane_depth_tint[j]);
        }
}

void init_world(void)
{
    init_lanes();
    int lane_depth_darkness_lvl = 18;
    for (int i = 0; i < WORLD_LANES_H; i++)
        lane_depth_tint[i] = (Color){255 - lane_depth_darkness_lvl * i, 255 - lane_depth_darkness_lvl * i, 255, 255}; // Init depth shading color values
}

void update_world(float dt)
{
}

void draw_world()
{
    draw_lanes();
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


