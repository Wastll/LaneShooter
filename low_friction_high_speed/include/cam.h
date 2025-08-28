#ifndef CAM_H
#define CAM_H

#include "raylib.h"

void init_cam(void);

void update_cam(float vel);

Camera3D *get_cam(void);

#endif