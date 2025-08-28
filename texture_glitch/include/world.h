#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"

#define WORLD_LANES_W 64
#define WORLD_LANES_H 5

typedef struct {
    Texture2D texture;
    float friction;
    bool is_solid;
} GroundTile;

void init_world(void);
void update_world(float dt);
void draw_lanes(void);
void draw_background(int fb_w, int fb_h);

#endif