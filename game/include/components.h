
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "raylib.h"

extern Vector3 positions[MAX_ENTITIES];
extern Vector3 velocities[MAX_ENTITIES];
extern Vector3 accelerations[MAX_ENTITIES];
extern Vector3 max_velocities[MAX_ENTITIES];

extern float frictions[MAX_ENTITIES];

extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasAcceleration[MAX_ENTITIES];
extern bool hasMaxVelocity[MAX_ENTITIES];

extern bool hasFriction[MAX_ENTITIES];

#endif