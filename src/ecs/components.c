#include "components.h"

char* names[MAX_ENTITIES] = {""};

// --- ECS usage flags ---

bool hasName[MAX_ENTITIES] = {false};
bool keyboard_controlled[MAX_ENTITIES] = {false};

// --- Rendering ---

AnimationComponent animations[MAX_ENTITIES] = {0};
Texture2D sprites[MAX_ENTITIES] = {0};
Vector3 origin_offsets[MAX_ENTITIES] = {0};
BillboardRenderer billboard_renderers[MAX_ENTITIES] = {0};
ModelRenderer model_renderers[MAX_ENTITIES] = {0};
CameraComp cameras[MAX_ENTITIES] = {0};
MultiModelRenderer multi_model_renderers[MAX_ENTITIES] = {0};

// --- Rendering usage flags ---

bool hasAnimation[MAX_ENTITIES] = {false};
bool hasSprite[MAX_ENTITIES] = {false};
bool hasBillboardRenderer[MAX_ENTITIES] = {false};
bool hasModelRenderer[MAX_ENTITIES] = {false};
bool hasCameraComp[MAX_ENTITIES] = {false};
bool hasMultiModelRenderer[MAX_ENTITIES] = {false};

// --- Physics ---

Vector3 positions[MAX_ENTITIES] = {0};
Vector3 velocities[MAX_ENTITIES] = {0};
Vector3 accelerations[MAX_ENTITIES] = {0};
MovementParams movement_params[MAX_ENTITIES] = {0};
MoveIntent move_intents[MAX_ENTITIES] = {0};
BoundingBox bounding_boxes[MAX_ENTITIES] = {0};
Vector3 bounding_box_scales[MAX_ENTITIES] = {{1,1,1}};
Vector3 collision_states[MAX_ENTITIES] = {0};

float frictions[MAX_ENTITIES] = {0};

void (*physicsFunc[MAX_ENTITIES])(Entity, KeyMap*) = {0};

PropComp props[MAX_ENTITIES] = {0};

// --- Physics usage flags ---

bool hasOriginOffset[MAX_ENTITIES] = {false};
bool hasPosition[MAX_ENTITIES] = {false};
bool hasVelocity[MAX_ENTITIES] = {false};
bool hasAcceleration[MAX_ENTITIES] = {false};
bool hasFriction[MAX_ENTITIES] = {false};
bool hasMovementParams[MAX_ENTITIES] = {false};
bool hasMoveIntent[MAX_ENTITIES] = {false};
bool hasGravity[MAX_ENTITIES] = {false};
bool hasBoundingBox[MAX_ENTITIES] = {false};
bool hasBoundingBoxScale[MAX_ENTITIES] = {false};
bool hasCollisionState[MAX_ENTITIES] = {false};
bool hasProp[MAX_ENTITIES] = {false};
bool hasPlayerTag[MAX_ENTITIES] = {false};

// --- Init helpers ---

void add_name(Entity e,char* name){
    hasName[e]=true;
    names[e]=name;
}

void add_origin_offset(Entity e, Vector3 offset)
{
    origin_offsets[e] = offset;
    hasOriginOffset[e] = true;
}

void add_position(Entity e, Vector3 pos)
{
    positions[e] = pos;
    hasPosition[e] = true;
}

void add_velocity(Entity e, Vector3 vel)
{
    velocities[e] = vel;
    hasVelocity[e] = true;
}

void add_acceleration(Entity e, Vector3 acc)
{
    accelerations[e] = acc;
    hasAcceleration[e] = true;
}

void add_movement_params(Entity e, MovementParams params)
{
    movement_params[e] = params;
    hasMovementParams[e] = true;
}

void add_friction(Entity e, float friction)
{
    frictions[e] = friction;
    hasFriction[e] = true;
}

void add_bounding_box(Entity e, BoundingBox bb){
    bounding_boxes[e] = bb;
    hasBoundingBox[e] = true;
}

void add_bounding_box_scale(Entity e, Vector3 bb_scale){
    bounding_box_scales[e] = bb_scale;
    hasBoundingBoxScale[e] = true;
}

void add_collision_state(Entity e){
    hasCollisionState[e]=true;
    collision_states[e]=(Vector3){0,0,0};
}

void add_camera_comp(Entity e, CameraComp cam){
    cameras[e]=cam;
    hasCameraComp[e]=true;
}

void add_model_renderer(Entity e, ModelRenderer model_renderer){
    model_renderers[e] = model_renderer;
    hasModelRenderer[e]=true;
}

// Prefab spawners...