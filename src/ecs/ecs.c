#include "ecs.h"

bool entity_used[MAX_ENTITIES] = { false };

 Entity create_entity() {
    for (Entity i = 2; i < MAX_ENTITIES; i++) {
        if (!entity_used[i]) {
            entity_used[i] = true;
            return i;
        }
    }
    return MAX_ENTITIES;
}

Entity create_entity_name(char* name) {
    Entity e = create_entity();
    if (e != MAX_ENTITIES) add_name(e, name);
    return e;
}

void destroy_entity(Entity e) {
    if (e < MAX_ENTITIES) {
        entity_used[e] = false;
    }
}