#include "anim_defs.h"

AnimationSet player_animset;

void init_animation_defs(void)
{
    player_animset.mode = ANIM_DIRECTIONAL;
    player_animset.clip_map[ANIM_IDLE] = 0;
    player_animset.clip_map[ANIM_WALK] = 1;
    player_animset.clip_map[ANIM_RUN] = 2;

    player_animset.clips[0] = (Anim){get_assets()->player_spritesheet_idle, 0.35f, 4, 16, 32};
    player_animset.clips[1] = (Anim){get_assets()->player_spritesheet_walk, 0.2f, 4, 16, 32};
    player_animset.clips[2] = (Anim){get_assets()->player_spritesheet_run, 0.2f * (35.0f / 55.0f), 6, 16, 32};
}
