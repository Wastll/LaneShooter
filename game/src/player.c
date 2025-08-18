#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"
#include "stdio.h"

static Entity player = 1;

#define PLAYER_ACC_X 35.0f
#define PLAYER_FRIC 1.3f
#define PLAYER_MAX_VEL 1.75f

void init_player()
{
    entity_used[player] = true;

    // In cube units
    positions[player] = (Vector3){0, 0, -2.5};
    hasPosition[player] = true;

    velocities[player] = (Vector3){0, 0, 0};
    hasVelocity[player] = true;
    max_velocities[player] = (Vector3){PLAYER_MAX_VEL,0,0};
    hasMaxVelocity[player] = true;

    accelerations[player] = (Vector3){0, 0, 0};
    hasAcceleration[player] = true;

    frictions[player] = PLAYER_FRIC;
    hasFriction[player] = true;


    // apply_gravity(player);
}

void update_player()
{
    accelerations[player] = (Vector3){0, 0, 0};
    
    if (IsKeyDown(KEY_D))
        apply_acc(player, (Vector3){PLAYER_ACC_X, 0, 0});
    if (IsKeyDown(KEY_A))
        apply_acc(player, (Vector3){-PLAYER_ACC_X, 0, 0});
}

void draw_player(const Camera3D *cam)
{
    float scale = 2.0f;
    Vector3 pos = positions[player];

    Vector3 draw_pos = pos;
    draw_pos.y += scale / 2.0f;

    DrawBillboard(*cam, get_assets()->player_placeholder, draw_pos, scale, WHITE);
    DrawSphere(positions[player], 0.05f, PINK);
}
