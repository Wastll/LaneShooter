#include "systems.h"
#include "ecs.h"
#include "components.h"
#include "raymath.h"

#include <stdbool.h>

#define GRAVITY_ACCELERATION -9.81f
 
static bool hasPhysicsComponents(unsigned int entity)
{
    return entity_used[entity] && hasAcceleration[entity] && hasVelocity[entity] && hasPosition[entity];
}

void update_physics(float dt)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (hasPhysicsComponents(e))
        {
            velocities[e] = Vector3Add(velocities[e], Vector3Scale(accelerations[e], dt));
            positions[e] = Vector3Add(positions[e], Vector3Scale(velocities[e], dt));
        }
    }
}

int apply_gravity(unsigned int e)
{
    if (!hasPhysicsComponents(e))
        return -1;

    apply_acc(e, (Vector3){0, GRAVITY_ACCELERATION, 0});

    return 0;
}

int apply_vel(unsigned int e, Vector3 vel)
{
    if (!hasPhysicsComponents(e))
        return -1;

    velocities[e] = Vector3Add(velocities[e], vel);

    return 0;
}

int apply_acc(unsigned int e, Vector3 acc)
{
    if (!hasPhysicsComponents(e))
        return -1;

    accelerations[e] = Vector3Add(accelerations[e], acc);

    return 0;
}