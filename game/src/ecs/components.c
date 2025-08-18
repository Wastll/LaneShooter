#include "components.h"

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