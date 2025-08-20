#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"

static Entity player = 1;

#define PLAYER_ACC_X 35.0f
#define PLAYER_ACC_Z 105.0f
#define PLAYER_FRIC 1.3f
#define PLAYER_MAX_VEL 1.75f

Anim anim_walk;
Anim anim_idle;
Anim anim_run;

Vector2 movment_vec;         // Unit vector representing the current direction of movment (updates every frame)
Vector2 direction_vec = {0}; // Unit vector representing the LAST direction of movment (updates only on player movement to preserve direction)
static int cycle_index = 0;

void init_player()
{
    entity_used[player] = true;

    sprites[player] = get_assets()->player_placeholder;
    hasSprite[player] = true;

    hasAnimation[player] = true;

    // In cube units
    positions[player] = (Vector3){0, 0, -2.5};
    hasPosition[player] = true;

    velocities[player] = (Vector3){0, 0, 0};
    hasVelocity[player] = true;
    max_velocities[player] = (Vector3){PLAYER_MAX_VEL, PLAYER_MAX_VEL, 3};
    hasMaxVelocity[player] = true;

    accelerations[player] = (Vector3){0, 0, 0};
    hasAcceleration[player] = true;

    frictions[player] = PLAYER_FRIC;
    hasFriction[player] = true;

    anim_walk = (Anim){get_assets()->player_spritesheet_walk, 0, 4, 0.2f, 0, 16, 32, cycle_index};
    anim_idle = (Anim){get_assets()->player_spritesheet_idle, 0, 4, 0.4f, 0, 16, 32, cycle_index};
    anim_run = (Anim){get_assets()->player_spritesheet_run, 0, 6, 0.2f, 0, 16, 32, cycle_index};

    // apply_gravity(player);
}

static int get_cycle_index(Vector2 dir)
{
    float angle = atan2f(dir.y, dir.x);
    if (angle < 0)
        angle += 2 * PI;

    int idx = (int)(angle / (PI / 4) + 6) % 8;
    return (idx > 4) ? abs(idx - 8) : idx;
}

void update_player()
{
    accelerations[player] = (Vector3){0, 0, 0};

    if (IsKeyDown(KEY_D))
    {
        apply_acc(player, (Vector3){PLAYER_ACC_X, 0, 0});
    }
    if (IsKeyDown(KEY_A))
    {
        apply_acc(player, (Vector3){-PLAYER_ACC_X, 0, 0});
    }
    if (IsKeyDown(KEY_W))
    {
        apply_acc(player, (Vector3){0, 0, -PLAYER_ACC_Z});
    }
    if (IsKeyDown(KEY_S))
    {
        apply_acc(player, (Vector3){0, 0, PLAYER_ACC_Z});
    }

    Vector2 new_dir = {0, 0};
    if (IsKeyDown(KEY_D))
        new_dir.x += 1;
    if (IsKeyDown(KEY_A))
        new_dir.x -= 1;
    if (IsKeyDown(KEY_W))
        new_dir.y -= 1;
    if (IsKeyDown(KEY_S))
        new_dir.y += 1;

    if (new_dir.x != 0 || new_dir.y != 0)
    {
        direction_vec = Vector2Normalize(new_dir);
    }

    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) || (movment_vec.x == 0 && movment_vec.y == 0))
    {
        if (animations[player].tex.id != anim_idle.tex.id)
        {
            animations[player] = anim_idle;
            direction_vec = Vector2Normalize(direction_vec);
        }
    }
    else
    {
        if (animations[player].tex.id != anim_walk.tex.id)
        {
            animations[player] = anim_walk;
        }
        direction_vec = Vector2Normalize(direction_vec);
        cycle_index = get_cycle_index(direction_vec);
    }
    movment_vec = Vector2Normalize((Vector2){accelerations[player].x, accelerations[player].z});
}

void draw_player(const Camera3D *cam)
{
    float scale = 2.0f;
    Vector3 pos = positions[player];

    Vector3 draw_pos = pos;
    draw_pos.y += scale / 2.0f;

    if (hasAnimation[player])
    {
        Anim *anim = &animations[player];
        Rectangle src = {
            .x = anim->frame * anim->frameWidth,
            .y = cycle_index * anim->frameHeight,
            .width = anim->frameWidth, // -1 to avoid bleeding
            .height = anim->frameHeight};

        DrawBillboardRec(*cam, anim->tex, src,
                         draw_pos, (Vector2){(direction_vec.x > 0) ? -1 : 1, 2}, // (-)1 WU wide, 2 WU tall
                         WHITE);
    }

    DrawSphere(positions[player], 0.05f, PINK);
}
