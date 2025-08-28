// world.c
#include "world.h"
#include "assets.h"
#include "world_props.h"

Color lane_depth_tint[WORLD_LANES_H];
static GroundTile ground_tiles[WORLD_LANES_W][WORLD_LANES_H];

static GroundTile init_ground_tile(Texture2D texture, float fric, bool is_solid){
    return (GroundTile){texture,fric,is_solid};
}

void init_world(void)
{
    int lane_depth_darkness_lvl = 18;
    for (int i = 0; i < WORLD_LANES_H; i++){   
        lane_depth_tint[i] = (Color){255 - lane_depth_darkness_lvl * i, 255 - lane_depth_darkness_lvl * i, 255, 255}; // Init depth shading color values
        for (int j = 0; j < WORLD_LANES_W; j++) 
            ground_tiles[j][i]=init_ground_tile(get_assets()->texture_meadow,1.f,true);
    }
    
    init_props();
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

    for (int i = 0; i < WORLD_LANES_W; i++)
        for (int j = 0; j < WORLD_LANES_H; j++)
        {
            Vector3 cube_pos =
                (Vector3){
                    i * cube_scale + cube_scale / 2,
                    -cube_scale / 2,
                    -j * cube_scale - cube_scale / 2};
            get_assets()->cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ground_tiles[i][j].texture;

            DrawModel(get_assets()->cube, cube_pos, cube_scale, lane_depth_tint[j]);
        }

        draw_props();
}
