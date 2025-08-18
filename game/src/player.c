#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"
#include "stdio.h"

static Entity player = 0;

void init_player()
{
    entity_used[player] = true;

    // In cube units
    positions[player] = (Vector3){0, 0, -2.5};
    hasPosition[player] = true;

    velocities[player] = (Vector3){0, 0, 0};
    hasVelocity[player] = true;

    accelerations[player] = (Vector3){0, 0, 0};
    hasAcceleration[player] = true;
    
    // apply_gravity(player);
}

void update_player()
{
    // Temporary z controls for alignment
    float speed = 0.5f;

    if (IsKeyDown(KEY_W)) positions[player].z += speed;
    if (IsKeyDown(KEY_S)) positions[player].z -= speed;

    if (IsKeyDown(KEY_E)) positions[player].y += speed;
    if (IsKeyDown(KEY_Q)) positions[player].y -= speed;
}

void draw_player(const Camera3D *cam)
{
    float scale = 2.0f;
    Vector3 pos = positions[player];

    Vector3 draw_pos = pos;
    draw_pos.y += scale / 2.0f; // Align player bottom with y=0

    DrawBillboard(*cam, get_assets()->player_placeholder, draw_pos, scale, WHITE);
    DrawSphere(positions[player],0.05f,PINK);
}
