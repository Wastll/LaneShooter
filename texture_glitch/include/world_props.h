#ifndef WORLD_PROPS_H
#define WORLD_PROPS_H

#include "raylib.h"

typedef struct
{
    bool exisits;
    Model model;
    Texture2D texture;
    Vector2 pos;
    Vector3 size;
    bool breakable;
    float hardness;
} Prop;

void init_props(void);
void update_props(void);
void draw_props(void);

#endif