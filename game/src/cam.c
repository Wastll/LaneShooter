#include "cam.h"
#include "ecs.h"
#include "systems.h"
#include "components.h"
#include "stdio.h"
#include "raymath.h"

static Camera3D cam;
static Entity e_cam = 0;

#define CAM_SPEED 0.7f
#define CAM_FRIC 1.4f

void init_cam(void)
{
    entity_used[e_cam] = true;

    // In cube units
    positions[e_cam] = (Vector3){0, 4.5f, 3.5f};
    hasPosition[e_cam] = true;

    velocities[e_cam] = (Vector3){0, 0, 0};
    hasVelocity[e_cam] = true;

    accelerations[e_cam] = (Vector3){0, 0, 0};
    hasAcceleration[e_cam] = true;

    frictions[e_cam] = CAM_FRIC;
    hasFriction[e_cam] = true;

    cam = (Camera3D){0};
    cam.position = positions[e_cam];
    cam.target = (Vector3){0, 0.0f, -2.5f};
    cam.up = (Vector3){0, 1, 0};
    cam.fovy = 60.0f;

    cam.projection = CAMERA_PERSPECTIVE;
}

void update_cam()
{

    if (IsKeyDown(KEY_D))
        apply_vel(e_cam, (Vector3){CAM_SPEED, 0, 0});
    if (IsKeyDown(KEY_A))
        apply_vel(e_cam, (Vector3){-CAM_SPEED, 0, 0});

    cam.position = positions[e_cam];

    // Slight camera tilt in direction of movement
    float target_x = positions[e_cam].x + 0.2f * velocities[e_cam].x;
    cam.target.x = Lerp(cam.target.x, target_x, 0.1f);
}

Camera3D *get_cam(void)
{
    return &cam;
}