
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "raylib.h"

// --- Textures ---

typedef struct {
    Texture2D tex;
    int frame;
    int maxFrames;
    float frameTime;
    float timer;
    int frameWidth;
    int frameHeight;
    int cycleIndex;
} Anim;

extern Texture2D sprites[MAX_ENTITIES];
extern Anim animations[MAX_ENTITIES];

extern bool hasSprite[MAX_ENTITIES];
extern bool hasAnimation[MAX_ENTITIES];

// --- Physics ---

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