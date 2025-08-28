#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "components.h"


typedef struct {
    float acc_walk;
    float acc_run;
    float walk_max_vel;
    float run_max_vel;
    float friction;

    float acc_x;
    float acc_z;
    float max_vel;

    Vector2 movement_vec;
    Vector2 direction_vec;
    int cycle_index;

    Anim anim_walk;
    Anim anim_idle;
    Anim anim_run;
} PlayerData;


void init_player(void);
void update_player(void);
void draw_player(const Camera3D* cam);

#endif