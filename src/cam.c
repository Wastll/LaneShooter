#include "cam.h"
#include "components.h"
#include "world.h"
#include "my_utils.h"

static Entity e_cam;

#define CAM_FRIC 1.5f
#define CAM_START_POS (Vector3){0, 4.5f, 3.5f}
#define CAM_TARGET_POS (Vector3){0, 0.0f, -WORLD_LANES_H/2.0f}

void init_cam(void)
{
    e_cam=create_entity_name("Camera");

    add_position(e_cam, CAM_START_POS);
    add_velocity(e_cam, (Vector3){0,0,0});
    add_friction(e_cam, CAM_FRIC);
    add_acceleration(e_cam, (Vector3){0,0,0});

    hasCameraComp[e_cam] = true;
    cameras[e_cam] = (CameraComp){
        .cam = {
            .position = CAM_START_POS,
            .target   = CAM_TARGET_POS,
            .up       = {0,1,0},
            .fovy     = 60.0f,
            .projection = CAMERA_PERSPECTIVE
        },
        .track_id = find_player_entity(),
        .velocity_displacement = {0.2f, 0, 0},
        .follow_lerp = 0.1f
    };
}

Camera3D *get_cam(void)
{
    return &cameras[e_cam].cam;
}