
#ifndef ANIMDEFS_H
#define ANIMDEFS_H

#include "assets.h"

typedef enum {
    ANIM_IDLE,
    ANIM_WALK,
    ANIM_RUN,
    ANIM_COUNT,
} AnimationID;

extern AnimationSet player_animset;

void init_animation_defs(void);

#endif
