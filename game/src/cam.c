#include "cam.h"
#include "ecs.h"
#include "systems.h"
#include "components.h"
#include "stdio.h"
#include "raymath.h"
#include "world.h"

static Camera3D cam;
static Entity e_cam = 0;

#define CAM_FRIC 1.5f
#define CAM_START_POS (Vector3){0, 4.5f, 3.5f}
#define CAM_TARGET_POS (Vector3){0, 0.0f, -WORLD_LANES_H/2.0f}

void init_cam(void)
{
    entity_used[e_cam] = true;

    add_position(e_cam, CAM_START_POS);
    add_velocity(e_cam, (Vector3){0});
    add_acceleration(e_cam, (Vector3){0});
    add_friction(e_cam, CAM_FRIC);

    // Initialize camera
    cam = (Camera3D){0};
    cam.position = positions[e_cam];
    cam.target = CAM_TARGET_POS;
    cam.up = (Vector3){0, 1, 0};
    cam.fovy = 60.0f;

    cam.projection = CAMERA_PERSPECTIVE;
}

void update_cam(float vel)
{
    apply_vel(e_cam, (Vector3){vel, 0, 0});

    cam.position = positions[e_cam];

    // Slight camera tilt in direction of movement
    float target_x = positions[e_cam].x + 0.2f * velocities[e_cam].x;
    cam.target.x = Lerp(cam.target.x, target_x, 0.1f);
}

Camera3D *get_cam(void)
{
    return &cam;
}