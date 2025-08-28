#include "ecs.h"
#include <stdbool.h>

bool entity_used[MAX_ENTITIES] = { false };

 Entity create_entity(void) {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
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
