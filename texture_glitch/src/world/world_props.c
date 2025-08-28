#include "world_props.h"
#include "world.h"
#include "assets.h"
#include "raymath.h"
#include "stdio.h"

#define MAX_PROPS 100

static Prop props[MAX_PROPS];

static Prop init_prop(bool exists, Model model, Texture2D texture, Vector2 pos, Vector3 size, bool breakable, float hardness)
{
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    return (Prop){exists, model, texture, pos, size, breakable, hardness};
}

void init_props(void)
{
    for (int i = 0; i < MAX_PROPS; i++)
        props[i].exisits = false;
    props[0] = init_prop(true, get_assets()->cube, get_assets()->missing_uv, (Vector2){3, 4}, (Vector3){1}, false, 1.f);

}

void update_props(void) {}
void draw_props(void)
{
    for (int i = 0; i < MAX_PROPS; i++)
    {
        if(!props[i].exisits) continue;
        Vector3 prop_draw_pos =
            (Vector3){
                props[i].pos.x,
                1,
                props[i].pos.y};

        DrawModel(props[i].model, prop_draw_pos, 1, WHITE);
    }
}
