#include "components.h"

// --- Textures ---

Anim animations[MAX_ENTITIES] = {0};
Texture2D sprites[MAX_ENTITIES] = {0};

// --- Textures usgage flags ---

bool hasAnimation[MAX_ENTITIES] = {false};
bool hasSprite[MAX_ENTITIES] = {false};

// --- Physics ---

Vector3 positions[MAX_ENTITIES] = {0};
Vector3 velocities[MAX_ENTITIES] = {0};
Vector3 accelerations[MAX_ENTITIES] = {0};
Vector3 max_velocities[MAX_ENTITIES] = {0};

float frictions[MAX_ENTITIES] = {0};

// --- Physics usage flages ---

bool hasPosition[MAX_ENTITIES] = {false};
bool hasVelocity[MAX_ENTITIES] = {false};
bool hasAcceleration[MAX_ENTITIES] = {false};
bool hasFriction[MAX_ENTITIES] = {false};
bool hasMaxVelocity[MAX_ENTITIES] = {false};
bool hasGravity[MAX_ENTITIES] = {false};

// --- Init helpers ---

void add_position(Entity e, Vector3 pos)
{
    positions[e] = pos;
    hasPosition[e] = true;
}

void add_velocity(Entity e, Vector3 vel)
{
    velocities[e] = vel;
    hasVelocity[e] = true;
}

void add_acceleration(Entity e, Vector3 acc)
{
    accelerations[e] = acc;
    hasAcceleration[e] = true;
}

void add_max_velocity(Entity e, Vector3 max_vel)
{
    max_velocities[e] = max_vel;
    hasMaxVelocity[e] = true;
}

void add_friction(Entity e, float friction)
{
    frictions[e] = friction;
    hasFriction[e] = true;
}
