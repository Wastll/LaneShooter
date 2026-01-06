#include "raylib.h"
#include "world.h"
#include "assets.h"
#include "world_props.h"

#define DEPTH_DARKNESS 18
#define CUBE_SCALE 1.f // probably unnecessary

static void init_lanes(void)
{
    Entity e_lanes = create_entity_name("Ground");
    add_position(e_lanes, (Vector3){0, 0, 0});
    hasBoundingBox[e_lanes] = true;
    bounding_boxes[e_lanes].min = (Vector3){0, -1, -WORLD_LANES_H};
    bounding_boxes[e_lanes].max = (Vector3){WORLD_LANES_W, 0, 0};
    add_collision_state(e_lanes);

    hasMultiModelRenderer[e_lanes] = true;
    MultiModelRenderer *mmr = &multi_model_renderers[e_lanes];
    mmr->count = 0;

    for (int i = 0; i < WORLD_LANES_W; i++)
    {
        for (int j = 0; j < WORLD_LANES_H; j++)
        {
            if (mmr->count >= MAX_MODELS_PER_ENTITY)
                break;

            Vector3 cube_pos = {
                i * CUBE_SCALE +  CUBE_SCALE / 2,
                -CUBE_SCALE / 2,
                -j * CUBE_SCALE - CUBE_SCALE / 2};

            mmr->models[mmr->count++] = (ModelRenderer){
                .model = &get_assets()->cube_meadow,
                .offset = cube_pos,
                .scale = CUBE_SCALE,
                .tint = (Color){255 + cube_pos.z * DEPTH_DARKNESS, 255 + cube_pos.z * DEPTH_DARKNESS, 255, 255}};
        }
    }
}

void init_world(void)
{
    init_props();
    init_lanes();
}

void draw_background(int fb_w, int fb_h)
{
    DrawTexturePro(
        get_assets()->skybox,
        (Rectangle){0, 0, get_assets()->skybox.width, get_assets()->skybox.height},
        (Rectangle){0, 0, fb_w, fb_h},
        (Vector2){0, 0}, 0, WHITE);
}
