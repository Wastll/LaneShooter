#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "raylib.h"

void update_physics(float dt);
int apply_gravity(unsigned int e);
int apply_vel(unsigned int e, Vector3 vel);
int apply_acc(unsigned int e, Vector3 acc);
void render_billboards(const Camera3D* cam);
void camera_system(void);
void render_models(void);
void render_multi_models(void);
void input_system(void);
void animation_system(float dt);

#endif