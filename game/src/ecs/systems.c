#include "systems.h"
#include "ecs.h"
#include "components.h"
#include "raymath.h"
#include "stdio.h"

#include <stdbool.h>

#define GRAVITY_ACCELERATION -9.81f

void update_animation(Entity e, float dt) {
    if (!hasAnimation[e]) return;

    
    Anim *anim = &animations[e];
    anim->timer += dt;
    if (anim->timer >= anim->frameTime) {
        anim->frame++;
        if (anim->frame >= anim->maxFrames) anim->frame = 0;
        anim->timer = 0;
    }
}

static bool hasPhysicsComponents(unsigned int entity)
{
    return entity_used[entity] && hasAcceleration[entity] && hasVelocity[entity] && hasPosition[entity] && hasFriction[entity];
}

void update_physics(float dt)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (hasPhysicsComponents(e))
        {
            velocities[e] = Vector3Add(velocities[e], Vector3Scale(accelerations[e], dt));

            
            float damping = powf(frictions[e], dt * 60.0f);
            velocities[e].x /= damping;
            velocities[e].y /= damping;
            velocities[e].z /= damping;
            
            if (hasMaxVelocity[e])
            {
                velocities[e].x = Clamp(velocities[e].x, -max_velocities[e].x, max_velocities[e].x);
                velocities[e].y = Clamp(velocities[e].y, -max_velocities[e].y, max_velocities[e].y);
                velocities[e].z = Clamp(velocities[e].z, -max_velocities[e].z, max_velocities[e].z);
            }

            positions[e] = Vector3Add(positions[e], Vector3Scale(velocities[e], dt));
            
            // printf("%d : %f\n", e, velocities[e].x);
        }

        if(hasAnimation[e]){
            update_animation(e,dt);
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