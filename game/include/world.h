#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"


#define WORLD_LANES_W 64
#define WORLD_LANES_H 5

void init_world(void);
void update_world(float dt);
void draw_world(void);
void draw_background(int fb_w, int fb_h);

#endif