#include "player.h"
#include "components.h"
#include "anim_defs.h"

void init_player()
{
    Entity player=create_entity_name("Player");
    hasPlayerTag[player] = true;
    keyboard_controlled[player] = true;

    add_position(player, (Vector3){2, 3, -1.f});
    add_velocity(player, (Vector3){0});
    add_acceleration(player, (Vector3){0});
    add_friction(player, 1.3f);

    hasBoundingBox[player] = true;
    bounding_boxes[player].min = (Vector3){-0.25, 0, -0.25};
    bounding_boxes[player].max = (Vector3){0.25, 1.3, 0.25};

    hasGravity[player] = true;
    hasAnimation[player] = true;
    add_collision_state(player);

    MovementParams mp = {
        .walk_acc     = 35.0f,
        .run_acc      = 55.0f,
        .walk_max_vel = 1.75f,
        .run_max_vel  = 3.0f,
        .air_max_vel  = 4.0f,
        .jump_vel     = 8.0f
    };

    movement_params[player] = mp;
    hasMovementParams[player] = true;
    hasMoveIntent[player] = true;
    
    hasBillboardRenderer[player] = true;
    billboard_renderers[player] = (BillboardRenderer){
        .offset = (Vector3){0, 1.0f, 0},
        .size = (Vector2){1.0f, 2.0f},
        .tint = WHITE};

    animations[player].set = &player_animset;
}