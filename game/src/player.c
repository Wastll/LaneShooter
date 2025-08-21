#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"

static Entity player = 1;
static PlayerData pdata;

static void handle_player_input();
static void update_player_anim();

void init_player()
{
    entity_used[player] = true;

    positions[player] = (Vector3){0, 5, -2.5f};
    hasPosition[player] = true;

    velocities[player] = (Vector3){0, 0, 0};
    hasVelocity[player] = true;
    
    accelerations[player] = (Vector3){0, 0, 0};
    hasAcceleration[player] = true;
    
    frictions[player] = 1.3f;
    hasFriction[player] = true;
    
    max_velocities[player] = (Vector3){0,3,0};
    hasMaxVelocity[player] = true;
    
    hasGravity[player] = true;

    hasAnimation[player] = true;

    pdata.acc_walk = 35.0f;
    pdata.acc_run = 55.0f;

    pdata.walk_max_vel = 1.75f;
    pdata.run_max_vel = 3.00f;
    pdata.in_air_max_vel = 4.00f;

    pdata.is_in_air = false;

    pdata.direction_vec = (Vector2){0};
    pdata.movement_vec = (Vector2){0};
    
    pdata.anim_walk = (Anim){get_assets()->player_spritesheet_walk, 0, 4, 0.2f, 0, 16, 32, pdata.cycle_index};
    pdata.anim_idle = (Anim){get_assets()->player_spritesheet_idle, 0, 4, 0.35f, 0, 16, 32, pdata.cycle_index};
    pdata.anim_run = (Anim){get_assets()->player_spritesheet_run, 0, 6, 0.2f * pdata.walk_max_vel / pdata.run_max_vel, 0, 16, 32, pdata.cycle_index};
    pdata.cycle_index = 0;
}

static int get_cycle_index(Vector2 dir)
{
    float angle = atan2f(dir.y, dir.x);
    if (angle < 0)
        angle += 2 * PI;

    int idx = (int)(angle / (PI / 4) + 6) % 8;
    return (idx > 4) ? abs(idx - 8) : idx;
}

static void switch_anim(Anim anim)
{
    if (animations[player].tex.id != anim.tex.id)
        animations[player] = anim;
}

void update_player()
{
    handle_player_input();
    update_player_anim();
}

static void handle_player_input()
{
    accelerations[player] = (Vector3){0};
    Vector2 new_dir = {0};
    Vector3 new_acc = {0};

    pdata.is_in_air = positions[player].y > 0;

    float acc = IsKeyDown(KEY_LEFT_SHIFT) ? pdata.acc_run : pdata.acc_walk;
    float max_vel = IsKeyDown(KEY_LEFT_SHIFT) ? (pdata.is_in_air ? pdata.in_air_max_vel : pdata.run_max_vel) : pdata.walk_max_vel;
    max_velocities[player] = (Vector3){ max_vel, 0, max_vel };

    if (IsKeyDown(KEY_D)) new_acc.x += acc, new_dir.x += 1;
    if (IsKeyDown(KEY_A)) new_acc.x -= acc, new_dir.x -= 1;
    if (IsKeyDown(KEY_W)) new_acc.z -= acc, new_dir.y -= 1;
    if (IsKeyDown(KEY_S)) new_acc.z += acc, new_dir.y += 1;
    if (IsKeyReleased(KEY_SPACE) && !pdata.is_in_air) apply_vel(player, (Vector3){0,8,0});

    apply_acc(player, new_acc);
    apply_gravity(player);

    if (new_dir.x != 0 || new_dir.y != 0)
        pdata.direction_vec = Vector2Normalize(new_dir);
    pdata.movement_vec = Vector2Normalize((Vector2){ accelerations[player].x, accelerations[player].z });
}


static void update_player_anim()
{
    if (pdata.movement_vec.x == 0 && pdata.movement_vec.y == 0)
        switch_anim(pdata.anim_idle);
    else
        switch_anim(IsKeyDown(KEY_LEFT_SHIFT) ? pdata.anim_run : pdata.anim_walk);

    // Horizontal sprite flip if player moving to the right
    if (pdata.direction_vec.x > 0 && animations[player].tex.width > 0)
        animations[player].tex.width *= -1;
    if (pdata.direction_vec.x <= 0)
        animations[player].tex.width = abs(animations[player].tex.width);

    pdata.cycle_index = get_cycle_index(pdata.direction_vec);
}

void draw_player(const Camera3D *cam)
{
    Vector3 pos = positions[player];
    Vector3 draw_pos = pos;
    draw_pos.y += 1; // Draw player 1 WU higher so the origin is at the bottom

    if (hasAnimation[player])
    {
        Anim *anim = &animations[player];
        Rectangle src = {
            .x = anim->frame * anim->frameWidth,
            .y = pdata.cycle_index * anim->frameHeight,
            .width = anim->frameWidth,
            .height = anim->frameHeight};

        DrawBillboardRec(*cam, anim->tex, src,
                         draw_pos, (Vector2){1, 2}, // (-)1 WU wide, 2 WU tall
                         WHITE);
    }

    DrawSphere(positions[player], 0.05f, PINK); // Player pos marker
}
