#include "world_props.h"
#include "world.h"
#include "assets.h"
#include "raymath.h"
#include "utils.h"
#include "components.h"
#include "stdio.h"

Vector3 prop_offset = {0.5f, -0.5f, -0.5f};

static PropComp init_prop(Entity e, Model *model, Vector3 pos, bool breakable, float hardness)
{
    hasProp[e] = true;
    add_position(e, pos);
    hasBoundingBox[e] = true;
    bounding_boxes[e] = GetModelBoundingBox(*model);
    hasCollision[e] = true;
    add_collision_state(e);
    add_origin_offset(e,prop_offset);
    return (PropComp){e, model, breakable, hardness};
}

static PropComp init_prop_bb_scaled(Entity e, Model *model, Vector3 pos, bool breakable, float hardness, Vector3 bb_scale)
{
    hasProp[e] = true;
    add_position(e, pos);
    hasBoundingBox[e] = true;
    bounding_boxes[e] = GetModelBoundingBox(*model);
    add_bounding_box_scale(e, bb_scale);
    hasCollision[e] = true;
    add_collision_state(e);
    add_origin_offset(e,prop_offset);
    return (PropComp){e, model, breakable, hardness};
}


void init_props(void)
{
    Entity floating_meadow = create_entity();
    props[floating_meadow] = init_prop(floating_meadow,&get_assets()->cube_meadow, (Vector3){4, 3, -2}, false, 1.f);

    Entity crate = create_entity();
    props[crate] = init_prop(crate,&get_assets()->cube_crate, (Vector3){4, 1, -1}, false, 1.f);

    Entity barrel = create_entity();
    props[barrel] = init_prop_bb_scaled(barrel,&get_assets()->cylinder_barrel, (Vector3){2, 1, -1}, false, 1.f,(Vector3){0.9f, 1.f, 0.9f});

    Entity tree = create_entity();
    props[tree] = init_prop_bb_scaled(tree,&get_assets()->tree, (Vector3){2, 2, -3}, false, 1.f, (Vector3){0.4f, 1.f, 0.4f});
}

void update_props(void)
{
}

void draw_props(void)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasProp[e]) continue;

        PropComp* prop_data = &props[e];
        DrawModel(*props[e].model,  Vector3Add(positions[e],prop_offset), 1, WHITE);

        // if (hasBoundingBox[e]) DrawBoundingBoxEx(e, RED);
    }

}
