#include "anim_handler.h"

void advance_animation(Entity e, float dt){
    if (!hasAnimation[e])
        return;
    
    AnimationComponent *animComp = &animations[e];
    animComp->timer += dt;
    if (animComp->timer >= animComp->set->clips[animComp->current_id].frameTime)
    {
        animComp->frame++;
        if (animComp->frame >= animComp->set->clips[animComp->current_id].maxFrames)
            animComp->frame = 0;
        animComp->timer -= animComp->set->clips[animComp->current_id].frameTime;
    }
}

void switch_animation(Entity e, int anim_id){
    if (!hasAnimation[e])
        return;

    AnimationComponent *animComp = &animations[e];
    if (animComp->current_id != anim_id)
    {
        animComp->current_id = anim_id;
        animComp->frame = 0;
        animComp->timer = 0.0f;
    }
}

// dumbed down 8-directional cycle index (less memory usage)
int get_cycle_index(Entity e)
{
    Vector2 dir = move_intents[e].move;

    if (dir.x != 0 || dir.y != 0)
        animations[e].last_dir = dir;

    Vector2 use_dir = (dir.x != 0 || dir.y != 0) ? dir : animations[e].last_dir;

    float x = use_dir.x;
    float y = use_dir.y;

    if (x > 0 && y < 0) { animations[e].flip_x = true;  return 3; } // forward-right
    if (x < 0 && y < 0) { animations[e].flip_x = false; return 3; } // forward-left
    if (x > 0 && y > 0) { animations[e].flip_x = true;  return 1; } // back-right
    if (x < 0 && y > 0) { animations[e].flip_x = false; return 1; } // back-left

    if (y < 0) return 4;                                            // forward
    if (y > 0) return 0;                                            // backward
    if (x > 0) { animations[e].flip_x = true;  return 2; }          // right
    if (x < 0) { animations[e].flip_x = false; return 2; }          // left

    return 0;
}