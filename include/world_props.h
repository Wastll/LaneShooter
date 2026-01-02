#ifndef WORLD_PROPS_H
#define WORLD_PROPS_H

#include "raylib.h"
#include "ecs.h"

typedef struct
{
    Entity e;
    Model* model;
    bool breakable;
    float hardness;
} PropComp;

PropComp props[MAX_ENTITIES];
bool hasProp[MAX_ENTITIES]; // Indicates if an entity has a prop component

void init_props(void);
void update_props(void);
void draw_props(void);

#endif