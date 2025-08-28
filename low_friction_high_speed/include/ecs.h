#ifndef ECS_H
#define ECS_H

#include <stdbool.h>

typedef unsigned int Entity;
#define MAX_ENTITIES 1000

extern bool entity_used[MAX_ENTITIES];

Entity create_entity(void);

void destroy_entity(Entity e);

#endif
