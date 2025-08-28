#include "world_props.h"
#include "world.h"
#include "assets.h"
#include "raymath.h"
#include "utils.h"
#include "components.h"
#include "stdio.h"

#define MAX_PROPS 100

static Prop props[MAX_PROPS];

static Prop init_prop(bool exists, Entity e, Model *model, Vector2 pos, Vector3 size, bool breakable, float hardness)
{
    return (Prop){exists, e, model, pos, size, breakable, hardness};
}

static Entity p_0;
static Entity p_1;

void init_props(void)
{
    for (int i = 0; i < MAX_PROPS; i++)
        props[i].exists = false;

    p_0 = create_entity();
    add_position(p_0, (Vector3){3, 1, -2.f});
    hasBoundingBox[p_0] = true;
    bounding_boxes[p_0].min = (Vector3){0,-1,-1};
    bounding_boxes[p_0].max = Vector3Add(bounding_boxes[p_0].min,(Vector3){1,1,1});
    hasCollision[p_0] = true;
    add_collision_state(p_0);

    props[0] = init_prop(true, p_0, &get_assets()->cube_meadow, (Vector2){3, 2.f}, (Vector3){1, 1, 1}, false, 1.f);

    p_1 = create_entity();
    add_position(p_1, (Vector3){2, 3, -1.f});
    hasBoundingBox[p_1] = true;
    bounding_boxes[p_1].min = (Vector3){0,-1,-1};
    bounding_boxes[p_1].max = Vector3Add(bounding_boxes[p_1].min,(Vector3){1,1,1});
    hasCollision[p_1] = true;
    add_collision_state(p_1);

    props[1] = init_prop(true, p_1, &get_assets()->cube,(Vector2){1, 3.f}, (Vector3){1,1,1}, false, 1.f);
    // props[2] = init_prop(true, &get_assets()->cube,(Vector2){1, 4.f}, (Vector3){1,1,1}, false, 1.f);
}

void update_props(void)
{
}

void draw_props(void)
{
    for (int i = 0; i < MAX_PROPS; i++)
    {
        if (!props[i].exists)
            continue;
        Entity prop_e = props[i].e;
        Vector3 prop_draw_pos =
            (Vector3){
                positions[prop_e].x + props[i].size.x / 2,
                positions[prop_e].y - 0.5f,
                positions[prop_e].z - props[i].size.z / 2};

        DrawModel(*props[i].model, prop_draw_pos, 1, WHITE);

        if (hasBoundingBox[props[i].e])
        {
            DrawBoundingBoxEx(prop_e, RED);
        }
    }
    // DrawBoundingBox(bounding_boxes[prop_e], PINK);
}
