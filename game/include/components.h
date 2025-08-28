
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "raylib.h"
#include "stdbool.h"

extern char* names[MAX_ENTITIES];

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

// --- Usage flags ---

extern bool hasName[MAX_ENTITIES];

// --- Textures ---

extern bool hasSprite[MAX_ENTITIES];
extern bool hasAnimation[MAX_ENTITIES];

// --- Physics ---

extern Vector3 positions[MAX_ENTITIES];
extern Vector3 velocities[MAX_ENTITIES];
extern Vector3 accelerations[MAX_ENTITIES];
extern Vector3 max_velocities[MAX_ENTITIES];
extern BoundingBox bounding_boxes[MAX_ENTITIES];

extern float frictions[MAX_ENTITIES];
extern Vector3 collision_states[MAX_ENTITIES]; 

// --- Physics---

extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasAcceleration[MAX_ENTITIES];
extern bool hasMaxVelocity[MAX_ENTITIES];
extern bool hasFriction[MAX_ENTITIES];
extern bool hasGravity[MAX_ENTITIES];
extern bool hasCollision[MAX_ENTITIES];
extern bool hasBoundingBox[MAX_ENTITIES];
extern bool hasCollisionState[MAX_ENTITIES];

// --- Init helpers ---

void add_name(Entity e, char* name);
void add_position(Entity e, Vector3 pos);
void add_velocity(Entity e, Vector3 vel);
void add_acceleration(Entity e, Vector3 acc);
void add_friction(Entity e, float fric);
void add_max_velocity(Entity e, Vector3 max_vel);
void add_bounding_box(Entity e, BoundingBox bb);
void add_collision_state(Entity e);

#endif