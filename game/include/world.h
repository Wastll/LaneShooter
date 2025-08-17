#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"

void init_world(void);
void update_world(float dt);
void draw_lanes(void);
void draw_background(int fb_w, int fb_h);

#endif