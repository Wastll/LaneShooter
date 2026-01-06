#ifndef MY_UTILS_H
#define MY_UTILS_H

#include "components.h"

void DrawBoundingBoxEx(Entity e, Color color);
int sign(float num);
bool array_contains_int(const int* arr, size_t len, int value);

// temporarly placed here until ecs_queries file is created
Entity find_player_entity(void);

#endif
