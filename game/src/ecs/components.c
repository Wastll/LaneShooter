#include "components.h"

// --- Textures ---

Anim animations[MAX_ENTITIES] = {0};
Texture2D sprites[MAX_ENTITIES] = {0};

bool hasAnimation[MAX_ENTITIES] = {false};
bool hasSprite[MAX_ENTITIES] = {false};

// --- Physics ---

Vector3 positions[MAX_ENTITIES] = {0};
Vector3 velocities[MAX_ENTITIES] = {0};
Vector3 accelerations[MAX_ENTITIES] = {0};
Vector3 max_velocities[MAX_ENTITIES] = {0};

float frictions[MAX_ENTITIES] = {0};

bool hasPosition[MAX_ENTITIES] = {false};
bool hasVelocity[MAX_ENTITIES] = {false};
bool hasAcceleration[MAX_ENTITIES] = {false};
bool hasFriction[MAX_ENTITIES] = {false};
bool hasMaxVelocity[MAX_ENTITIES] = {false};
bool hasGravity[MAX_ENTITIES] = {false};