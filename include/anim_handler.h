
#ifndef ANIMHANDLER_H
#define ANIMHANDLER_H

#include "components.h"

void advance_animation(Entity e, float dt);
void switch_animation(Entity e, int anim_id);
int get_cycle_index(Entity e);

#endif