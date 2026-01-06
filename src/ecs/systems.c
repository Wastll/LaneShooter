#include "systems.h"
#include "components.h"
#include "raymath.h"
#include "anim_handler.h"
#include "keyhandler.h"
#include "anim_defs.h"
#include "debug_system.h"

#pragma region Physics Systems

#define GRAVITY_ACCELERATION 3 * -9.81f // g, because physics

static bool hasPhysicsComponents(unsigned int entity)
{
    return entity_used[entity] && hasAcceleration[entity] && hasVelocity[entity] && hasPosition[entity] && hasFriction[entity];
}

static BoundingBox get_model_bounding_box(Entity e)
{
    BoundingBox box = bounding_boxes[e];

    ModelRenderer *mr = &model_renderers[e];

    if (hasBoundingBoxScale[e])
    {
        box.min = Vector3Add(Vector3Add(Vector3Multiply(box.min, bounding_box_scales[e]), positions[e]), mr->offset);
        box.max = Vector3Add(Vector3Add(Vector3Multiply(box.max, bounding_box_scales[e]), positions[e]), mr->offset);
    }
    else
    {
        box.min = Vector3Add(Vector3Add(box.min, positions[e]), mr->offset);
        box.max = Vector3Add(Vector3Add(box.max, positions[e]), mr->offset);
    }
    return box;
}


void handle_collisions(Entity e)
{
    BoundingBox boxE = get_model_bounding_box(e);

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

        BoundingBox boxO = get_model_bounding_box(o);

        if (CheckCollisionBoxes(boxE, boxO))
        {

            float overlapX = fmin(boxE.max.x, boxO.max.x) - fmax(boxE.min.x, boxO.min.x);
            float overlapY = fmin(boxE.max.y, boxO.max.y) - fmax(boxE.min.y, boxO.min.y);
            float overlapZ = fmin(boxE.max.z, boxO.max.z) - fmax(boxE.min.z, boxO.min.z);

            if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0)
                continue;

            Vector3 centerE = Vector3Scale(Vector3Add(boxE.min, boxE.max), 0.5f);
            Vector3 centerO = Vector3Scale(Vector3Add(boxO.min, boxO.max), 0.5f);

            Vector3 normal = {0, 0, 0};

            if (overlapY <= overlapX && overlapY <= overlapZ)
            {
                if (velocities[e].y < 0)
                {
                    positions[e].y += overlapY;
                    collision_states[e].y = -1;
                    normal = (Vector3){0, 1, 0};
                }
                else if (velocities[e].y > 0)
                {
                    positions[e].y -= overlapY;
                    collision_states[e].y = 1;
                    normal = (Vector3){0, -1, 0};
                }
            }
            else if (overlapX < overlapZ)
            {
                float dir = (centerE.x < centerO.x) ? -1.f : 1.f;
                collision_states[e].x = dir;
                positions[e].x += overlapX * dir;
                normal = (Vector3){dir, 0, 0};
            }
            else
            {
                float dir = (centerE.z < centerO.z) ? -1.f : 1.f;
                collision_states[e].z = dir;
                positions[e].z += overlapZ * dir;
                normal = (Vector3){0, 0, dir};
            }

            float vn = Vector3DotProduct(velocities[e], normal);
            if (vn < 0)
            {
                velocities[e] = Vector3Add(velocities[e], Vector3Scale(normal, -vn));
            }
        }
    }
}

void update_physics(float dt)
{

    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasPhysicsComponents(e))
            continue;
        MoveIntent *intent = &move_intents[e];
        float current_max_acc = intent->want_run ? movement_params[e].run_acc : movement_params[e].walk_acc;

        accelerations[e].x += intent->move.x * current_max_acc;
        accelerations[e].z += intent->move.y * current_max_acc;

        if (hasGravity[e])
            accelerations[e].y += GRAVITY_ACCELERATION;
        bool is_in_air = collision_states[e].y > -1;

        velocities[e] = Vector3Add(velocities[e], Vector3Scale(accelerations[e], dt));

        float damping = (hasCollisionState[e] && collision_states[e].y > -1 && e > 0) ? 1.02f : powf(frictions[e], dt * 60.0f);
        velocities[e].x /= damping;
        velocities[e].z /= damping;

        if (hasMovementParams[e])
        {
            Vector2 vel_xz = {velocities[e].x, velocities[e].z};
            float speed = Vector2Length(vel_xz);
            float max_speed = move_intents[e].want_run ? (is_in_air ? movement_params[e].air_max_vel : movement_params[e].run_max_vel) : (is_in_air ? movement_params[e].air_max_vel : movement_params[e].walk_max_vel);

            if (speed > max_speed && speed > 0.0f)
            {
                Vector2 clamped = Vector2Scale(vel_xz, max_speed / speed);
                velocities[e].x = clamped.x;
                velocities[e].z = clamped.y;
            }
        }

        if (!is_in_air)
            velocities[e].y += intent->want_jump * movement_params[e].jump_vel;

        positions[e] = Vector3Add(positions[e], Vector3Scale(velocities[e], dt));

        if (hasCollisionState[e])
            handle_collisions(e);

        accelerations[e] = (Vector3){0, 0, 0};
    }
}

#pragma endregion

#pragma region Rendering Systems

void render_billboards(const Camera3D *cam)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasBillboardRenderer[e])
            continue;

        BillboardRenderer *br = &billboard_renderers[e];

        Vector3 pos = positions[e];
        pos = Vector3Add(pos, br->offset);

        if (hasAnimation[e])
        {
            AnimationComponent *a = &animations[e];
            Anim *clip = &a->set->clips[a->current_id];

            Rectangle src = {
                .x = a->frame * clip->frameWidth,
                .y = get_cycle_index(e) * clip->frameHeight,
                .width = clip->frameWidth,
                .height = clip->frameHeight};

            if (a->flip_x)
            {
                src.x += src.width;
                src.width *= -1;
            }

            DrawBillboardRec(*cam, clip->tex, src,
                             pos, br->size, br->tint);
        }
        else
        {
            // Single texture billboards..
        }
    }
}

void render_models()
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasModelRenderer[e])
            continue;

        ModelRenderer *mr = &model_renderers[e];

        Vector3 pos = positions[e];
        pos = Vector3Add(pos, mr->offset);

        DrawModel(*mr->model, pos, mr->scale, mr->tint);
    }
}

void render_multi_models()
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasMultiModelRenderer[e])
            continue;

        MultiModelRenderer *mmr = &multi_model_renderers[e];
        Vector3 entity_pos = positions[e];

        for (int i = 0; i < mmr->count; i++)
        {
            ModelRenderer *mr = &mmr->models[i];
            Vector3 pos = Vector3Add(entity_pos, mr->offset);
            DrawModel(*mr->model, pos, mr->scale, mr->tint);
        }
    }
}

#pragma endregion

void camera_system(void)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasCameraComp[e])
            continue;

        CameraComp *cc = &cameras[e];
        Entity t = cc->track_id;
        if (t == MAX_ENTITIES)
            continue;

        float follow_input = positions[t].x - positions[e].x;

        apply_vel(e, (Vector3){follow_input, 0, 0});

        cc->cam.position = positions[e];

        float target_x =
            positions[e].x + cc->velocity_displacement.x * velocities[e].x;

        cc->cam.target.x = Lerp(cc->cam.target.x, target_x, cc->follow_lerp);
    }
}

void input_system(void)
{
    KeyMap *keys = get_keymap();

    if(keys->pressed[KEY_F1]) debug_bb_toggle();

    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasMoveIntent[e] || !hasMovementParams[e])
            continue;

        MoveIntent *intent = &move_intents[e];

        intent->want_run = keys->down[KEY_LEFT_SHIFT];
        intent->want_jump = keys->pressed[KEY_SPACE];
        intent->move = (Vector2){
            (keys->down[KEY_D] ? 1.0f : 0.0f) - (keys->down[KEY_A] ? 1.0f : 0.0f),
            (keys->down[KEY_S] ? 1.0f : 0.0f) - (keys->down[KEY_W] ? 1.0f : 0.0f)};
    }
}

void animation_system(float dt)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasAnimation[e])
            continue;

        AnimationComponent *a = &animations[e];

        switch (a->set->mode)
        {
        case ANIM_SINGLE:
            switch_animation(e, 0);
            break;

        case ANIM_DIRECTIONAL:
            if (move_intents[e].move.x == 0 && move_intents[e].move.y == 0)
                switch_animation(e, ANIM_IDLE);
            else
                switch_animation(e, move_intents[e].want_run ? ANIM_RUN : ANIM_WALK);
            break;
        }
    }

    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!hasAnimation[e])
            continue;
        advance_animation(e, dt);
    }
}

#pragma region Helper Functions

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

#pragma endregion