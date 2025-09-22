#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "components.h"


typedef struct PlayerData {
    float acc_walk;
    float acc_run;

    float walk_max_vel;
    float run_max_vel;
    float in_air_max_vel;

    bool is_in_air;
    
    Vector2 direction_vec;
    Vector2 acceleration_vec;

    Anim anim_idle;
    Anim anim_walk;
    Anim anim_run;
    int cycle_index;
} PlayerData;

void init_player(void);
void update_player(void);
void draw_player(const Camera3D* cam);

#endif