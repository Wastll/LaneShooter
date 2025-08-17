#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

void init_player(void);
void update_player(void);
void draw_player(const Camera3D* cam);

#endif