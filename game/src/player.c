#include "player.h"
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "assets.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"

#define PLAYER_WALK_ACC 35.0f
#define PLAYER_RUN_ACC 55.0f

#define PLAYER_WALK_VEL_MAX 1.75f
#define PLAYER_RUN_VEL_MAX 3.0f
#define PLAYER_IN_AIR_VEL_MAX 4.0f

#define PLAYER_JUMP_VEL 8.0f

#define ANIM_RUN_FRAME_TIME_RATIO (PLAYER_WALK_VEL_MAX / PLAYER_RUN_VEL_MAX)

static Entity player = 1;
static PlayerData pdata;

static void handle_player_input();
static void update_player_anim();

void init_player()
{
    entity_used[player] = true;

    add_position(player, (Vector3){0, 5, -2.5f});
    add_velocity(player, (Vector3){0});
    add_acceleration(player, (Vector3){0});
    add_max_velocity(player, (Vector3){0,3,0});
    add_friction(player, 1.3f);
    hasBoundingBox[player] = true;
    bounding_boxes[player].min = (Vector3){-0.25,0,-0.25};
    bounding_boxes[player].max = (Vector3){0.25,1.3,0.25};

    hasGravity[player] = true;
    hasAnimation[player] = true;
    hasCollision[player] = true;

    hasCollisionState[player] = true;
    add_collision_state(player);

    pdata.is_in_air = false;

    pdata.direction_vec = (Vector2){0};
    pdata.acceleration_vec = (Vector2){0};
    
    pdata.anim_walk = (Anim){get_assets()->player_spritesheet_walk, 0, 4, 0.2f, 0, 16, 32, pdata.cycle_index};
    pdata.anim_idle = (Anim){get_assets()->player_spritesheet_idle, 0, 4, 0.35f, 0, 16, 32, pdata.cycle_index};
    pdata.anim_run = (Anim){get_assets()->player_spritesheet_run, 0, 6, 0.2f * ANIM_RUN_FRAME_TIME_RATIO, 0, 16, 32, pdata.cycle_index};
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

    pdata.is_in_air = collision_states[player].y>-1;

    float acc = IsKeyDown(KEY_LEFT_SHIFT) ? PLAYER_RUN_ACC : PLAYER_WALK_ACC;
    float max_vel = IsKeyDown(KEY_LEFT_SHIFT) ? (pdata.is_in_air ? PLAYER_IN_AIR_VEL_MAX: PLAYER_RUN_VEL_MAX) : PLAYER_WALK_VEL_MAX;
    max_velocities[player] = (Vector3){ max_vel, 0, max_vel };

    if (IsKeyDown(KEY_D)) new_acc.x += acc, new_dir.x += 1;
    if (IsKeyDown(KEY_A)) new_acc.x -= acc, new_dir.x -= 1;
    if (IsKeyDown(KEY_W)) new_acc.z -= acc, new_dir.y -= 1;
    if (IsKeyDown(KEY_S)) new_acc.z += acc, new_dir.y += 1;
    if (IsKeyReleased(KEY_SPACE) && !pdata.is_in_air) apply_vel(player, (Vector3){0,PLAYER_JUMP_VEL,0});

    apply_acc(player, new_acc);
    apply_gravity(player);

    if (new_dir.x != 0 || new_dir.y != 0)
        pdata.direction_vec = Vector2Normalize(new_dir);
    pdata.acceleration_vec = Vector2Normalize((Vector2){ accelerations[player].x, accelerations[player].z });
}


static void update_player_anim()
{
    if (pdata.acceleration_vec.x == 0 && pdata.acceleration_vec.y == 0)
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

    int player_height = 2;
    draw_pos.y += player_height/2; // Draw player 1 WU higher so the origin is at the bottom

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
    DrawBoundingBoxEx(player,YELLOW);
    DrawSphere(positions[player], 0.05f, PINK); // Player pos marker
}
