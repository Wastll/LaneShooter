#ifndef WORLD_PROPS_H
#define WORLD_PROPS_H

#include "raylib.h"
#include "ecs.h"

typedef struct
{
    bool exists;
    Entity e;
    Model* model;
    Vector2 pos;
    Vector3 size;
    bool breakable;
    float hardness;
} Prop;

void init_props(void);
void update_props(void);
void draw_props(void);

#endif