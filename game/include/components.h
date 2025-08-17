
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "raylib.h"

extern Vector3 positions[MAX_ENTITIES];
extern Vector3 velocities[MAX_ENTITIES];
extern Vector3 accelerations[MAX_ENTITIES];
extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasAcceleration[MAX_ENTITIES];

#endif