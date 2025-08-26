#include "ecs.h"
#include <stdbool.h>

bool entity_used[MAX_ENTITIES] = { false };

 Entity create_entity(void) {
    // Reserve enitiy 0 for cam, entity 1 for player
    for (Entity i = 2; i < MAX_ENTITIES; i++) {
        if (!entity_used[i]) {
            entity_used[i] = true;
            return i;
        }
    }
    return MAX_ENTITIES;
}

void destroy_entity(Entity e) {
    if (e < MAX_ENTITIES) {
        entity_used[e] = false;
    }
}
