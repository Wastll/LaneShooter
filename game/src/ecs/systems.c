#include "systems.h"
#include "ecs.h"
#include "components.h"
#include "raymath.h"
#include "stdio.h"

#include <stdbool.h>

#define GRAVITY_ACCELERATION 3 * -9.81f

static bool hasPhysicsComponents(unsigned int entity)
{
    return entity_used[entity] && hasAcceleration[entity] && hasVelocity[entity] && hasPosition[entity] && hasFriction[entity];
}

static BoundingBox get_bounding_box(Entity e)
{
    BoundingBox box = bounding_boxes[e];

    box.min = Vector3Add(box.min, positions[e]);
    box.max = Vector3Add(box.max, positions[e]);

    return box;
}

static BoundingBox get_bounding_box_translate(Entity e, Vector3 translation)
{
    BoundingBox box = bounding_boxes[e];
    Vector3 trans_pos = Vector3Add(positions[e], translation);

    box.min = Vector3Add(box.min, trans_pos);
    box.max = Vector3Add(box.max, trans_pos);

    return box;
}

void update_animation(Entity e, float dt)
{
    if (!hasAnimation[e])
        return;

    Anim *anim = &animations[e];
    anim->timer += dt;
    if (anim->timer >= anim->frameTime)
    {
        anim->frame++;
        if (anim->frame >= anim->maxFrames)
            anim->frame = 0;
        anim->timer = 0;
    }
}

void update_physics(float dt)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (hasPhysicsComponents(e))
        {
            velocities[e] = Vector3Add(velocities[e], Vector3Scale(accelerations[e], dt));

            float damping = (hasCollisionState[e] && collision_states[e].y > -1 && e > 0) ? 1.02f : powf(frictions[e], dt * 60.0f);
            velocities[e].x /= damping;
            velocities[e].z /= damping;

            if (hasMaxVelocity[e])
            {
                // Directional scaling in xz-direction
                Vector2 vel_xz = {velocities[e].x, velocities[e].z};
                float speed = Vector2Length(vel_xz);
                float max_speed = fmaxf(max_velocities[e].x, max_velocities[e].z); // Use max val for now, may change later

                if (speed > max_speed && speed > 0.0f)
                {
                    Vector2 clamped = Vector2Scale(vel_xz, max_speed / speed);
                    velocities[e].x = clamped.x;
                    velocities[e].z = clamped.y;
                }
            }

            // Collision
            if (hasCollisionState[e])
            {
                BoundingBox boxE = get_bounding_box(e);
                collision_states[e] = (Vector3){0, 0, 0};

                for (Entity o = 0; o < MAX_ENTITIES; o++)
                {
                    if (o == e)continue;

                    BoundingBox boxO = get_bounding_box(o);

                    if (CheckCollisionBoxes(boxE, boxO))
                    {
                // collision_states[e] = (Vector3){0, 0, 0};
                // collision_states[o] = (Vector3){0, 0, 0};
                        printf("%d, %d\n",e,o);
                        if (velocities[e].y > 0 && boxE.max.y<positions[o].y )
                        {
                            positions[e].y = boxO.min.y -(boxE.max.y-boxE.min.y)-0.1f;
                            collision_states[e].y = 1;
                            velocities[e].y = 0;
                        }
                        if (velocities[e].y < 0 && positions[e].y<=(boxO.max.y-boxO.min.y) && positions[e].y!=boxO.min.y)
                        {
                            positions[e].y = boxO.max.y;
                            collision_states[e].y = -1;
                            velocities[e].y = 0;
                        }

                        // TODO: handle x/z collisions
                    }
                }
            }

            positions[e] = Vector3Add(positions[e], Vector3Scale(velocities[e], dt));
        }

        if (hasAnimation[e])
            update_animation(e, dt);
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