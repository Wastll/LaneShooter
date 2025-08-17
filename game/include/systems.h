#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "raylib.h"

void update_physics(float dt);
int apply_gravity(unsigned int e);
int apply_vel(unsigned int e, Vector3 vel);
int apply_acc(unsigned int e, Vector3 acc);

#endif