#include "systems.h"
#include "ecs.h"
#include "components.h"
#include "raymath.h"
#include "stdio.h"

#include "utils.h"
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
                if (collision_states[e].x != 0)
                    collision_states[e].x = 0;
                if (collision_states[e].y != 0)
                    collision_states[e].y = 0;
                if (collision_states[e].z != 0)
                    collision_states[e].z = 0;

                for (Entity o = 0; o < MAX_ENTITIES; o++)
                {
                    if (o == e)
                        continue;

                    BoundingBox boxO = get_bounding_box(o);

                    if (CheckCollisionBoxes(boxE, boxO))
                    {
                        // collision_states[e] = (Vector3){0, 0, 0};
                        // collision_states[o] = (Vector3){0, 0, 0};

                        // Foot coll
                        // if (boxE.min.y + (boxE.max.y - boxE.min.y) > boxO.min.y && !(boxE.min.y > boxO.min.y + (boxO.max.y - boxO.min.y)))
                        // {

                        //     // if(collision_states[e].x!=0&&collision_states[e].z!=0) ;
                        //     positions[e].y = boxO.min.y + (boxO.max.y - boxO.min.y);

                        //     collision_states[e].y = -1;
                        // }

                        // // Head coll
                        // if (boxE.min.y > boxO.min.y + (boxO.max.y - boxO.min.y) && !(boxE.min.y + (boxE.max.y - boxE.min.y) > boxO.min.y))
                        // {
                        //     positions[e].y = boxO.min.y - (boxO.max.y - boxO.min.y);
                        //     collision_states[e].y = 1;
                        // }



                        /*
                        Check algo:
                        X:
                            if player y on between block
                                if bb player Z is "inbetween" block
                                && if bb player X is NOT "inbetween" block / not elligable for Z colliding
                                    if bb player right x collides with block bb left
                                    && if player on left side of block

                                    if bb player left x collides with block bb right
                                    && if player on right side of block

                            if player x & z between block
                                if player
                                */
                               
                               if (
                                   boxE.max.x >= boxO.min.x && boxE.max.z >= boxO.min.z &&
                                   boxE.min.x <= boxO.max.x && boxE.min.z <= boxO.max.z )
                                   {
                                       // if (boxE.max.z >= boxO.min.z && boxE.min.z <= boxO.max.z && !(positions[e].x >= boxO.min.x && positions[e].x <= boxO.max.x))
                                       // {
                                        
                                       if (boxE.min.y <= boxO.max.y)
                                        {
                                            positions[e].y = boxO.max.y;
                                            collision_states[e].y = -1;
                                            // velocities[e].y = 0;                                            
                                        }
                                        // if (boxE.min.x < boxO.max.x &&
                                        //     positions[e].x > boxO.min.x + (boxO.max.x - boxO.min.x) / 2)
                                        // {
                                            //     positions[e].x = boxO.max.x + (boxE.max.x - boxE.min.x) / 2;
                                            //     collision_states[e].x = -1;
                                            // }
                                            // }
                                        }
                                        if (sign(velocities[e].y) == sign(collision_states[e].y))
                                            velocities[e].y = 0;


                        if (o != 4 && boxE.min.y >= boxO.min.y && boxE.min.y <= boxO.max.y) // remove o != 4
                        {
                            if (boxE.max.z >= boxO.min.z && boxE.min.z <= boxO.max.z && !(positions[e].x >= boxO.min.x && positions[e].x <= boxO.max.x))
                            {

                                if (boxO.min.x < boxE.max.x &&
                                    positions[e].x < boxO.min.x + (boxO.max.x - boxO.min.x) / 2)
                                {
                                    positions[e].x = boxO.min.x - (boxE.max.x - boxE.min.x) / 2;
                                    collision_states[e].x = 1;
                                }
                                if (boxE.min.x < boxO.max.x &&
                                    positions[e].x > boxO.min.x + (boxO.max.x - boxO.min.x) / 2)
                                {
                                    positions[e].x = boxO.max.x + (boxE.max.x - boxE.min.x) / 2;
                                    collision_states[e].x = -1;
                                }
                            }

                            if (boxE.max.x >= boxO.min.x && boxE.min.x <= boxO.max.x && !(positions[e].z >= boxO.min.z && positions[e].z <= boxO.max.z))
                            {

                                if (boxO.min.z < positions[e].z + (boxE.max.z - boxE.min.z) / 2 &&
                                    positions[e].z < boxO.min.z + (boxO.max.z - boxO.min.z) / 2)
                                {
                                    positions[e].z = boxO.min.z - (boxE.max.z - boxE.min.z) / 2;
                                    collision_states[e].z = 1;
                                }
                                if (positions[e].z - (boxE.max.z - boxE.min.z) / 2 < boxO.max.z &&
                                    positions[e].z > boxO.min.z + (boxO.max.z - boxO.min.z) / 2)
                                {
                                    positions[e].z = boxO.max.z + (boxE.max.z - boxE.min.z) / 2;
                                    collision_states[e].z = -1;
                                }
                            }
                        }
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