#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"

static Entity player = 0;

void init_player()
{
    entity_used[player] = true;

    positions[player] = (Vector3){512, 109, 80.5f};
    hasPosition[player] = true;

    velocities[player] = (Vector3){0, 0, 0};
    hasVelocity[player] = true;

    accelerations[player] = (Vector3){0, 0, 0};
    hasAcceleration[player] = true;
    
    // apply_gravity(player);
}

void update_player()
{
}

void draw_player(const Camera3D *cam)
{
    DrawBillboard(*cam, get_assets()->player_placeholder, positions[player], 0.56, WHITE);
}