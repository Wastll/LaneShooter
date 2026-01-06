
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs.h"
#include "raylib.h"
#include "keyhandler.h"

extern char* names[MAX_ENTITIES];

// --- Rendering ---

#define MAX_MODELS_PER_ENTITY 1024

// immutable clip structure
typedef struct {
    Texture2D tex;
    float frameTime;
    int maxFrames;
    int frameWidth;
    int frameHeight;
} Anim;
typedef enum {
    ANIM_SINGLE,
    ANIM_DIRECTIONAL
} AnimationMode;
typedef struct {
    Anim clips[8];
    int clip_map[8]; // maps logical animation IDs to clip indices
    AnimationMode mode;
} AnimationSet;

// mutable runtime animation component (per entity)
typedef struct {
    AnimationSet* set;
    int current_id;
    int frame;
    float timer;
    bool flip_x;
    Vector2 last_dir;
} AnimationComponent;

extern Texture2D sprites[MAX_ENTITIES];
extern AnimationComponent animations[MAX_ENTITIES];
extern Vector3 origin_offsets[MAX_ENTITIES]; // eventually replace with Renderer component offset

typedef struct {
    Vector3 offset;
    Vector2 size;
    Color tint;
} BillboardRenderer;

extern BillboardRenderer billboard_renderers[MAX_ENTITIES];

typedef struct {
    Model* model;
    Vector3 offset;
    float scale;
    Color tint;
} ModelRenderer;

extern ModelRenderer model_renderers[MAX_ENTITIES];

typedef struct {
    ModelRenderer models[MAX_MODELS_PER_ENTITY];
    int count;
} MultiModelRenderer;

extern MultiModelRenderer multi_model_renderers[MAX_ENTITIES];

typedef struct {
    Camera3D cam;
    Vector3 target;
    Vector3 up;
    float fovy;
    CameraProjection projection;
    Entity track_id;
    Vector3 velocity_displacement;
    float follow_lerp;
} CameraComp;

extern CameraComp cameras[MAX_ENTITIES];

// --- Usage flags ---

// --- ECS ---

extern bool hasName[MAX_ENTITIES];
extern bool keyboard_controlled[MAX_ENTITIES];

// --- Rendering ---

extern bool hasSprite[MAX_ENTITIES];
extern bool hasAnimation[MAX_ENTITIES];
extern bool hasOriginOffset[MAX_ENTITIES];
extern bool hasBillboardRenderer[MAX_ENTITIES];
extern bool hasModelRenderer[MAX_ENTITIES];
extern bool hasCameraComp[MAX_ENTITIES];
extern bool hasMultiModelRenderer[MAX_ENTITIES];

// --- Physics ---

typedef struct {
    float walk_acc;
    float run_acc;
    float walk_max_vel;
    float run_max_vel;
    float air_max_vel;
    float jump_vel;
} MovementParams;

typedef struct {
    Vector2 move;
    bool want_jump;
    bool want_run;
} MoveIntent;

typedef struct {
    Entity e;
    bool breakable;
    float hardness;
} PropComp;

extern PropComp props[MAX_ENTITIES];

extern Vector3 positions[MAX_ENTITIES];
extern Vector3 velocities[MAX_ENTITIES];
extern Vector3 accelerations[MAX_ENTITIES];
extern MovementParams movement_params[MAX_ENTITIES];
extern MoveIntent move_intents[MAX_ENTITIES];
extern BoundingBox bounding_boxes[MAX_ENTITIES];
extern Vector3 bounding_box_scales[MAX_ENTITIES];
extern float frictions[MAX_ENTITIES];
extern Vector3 collision_states[MAX_ENTITIES]; 

// --- Physics---

extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasAcceleration[MAX_ENTITIES];
extern bool hasMovementParams[MAX_ENTITIES];
extern bool hasMoveIntent[MAX_ENTITIES];
extern bool hasFriction[MAX_ENTITIES];
extern bool hasGravity[MAX_ENTITIES];
extern bool hasBoundingBox[MAX_ENTITIES];
extern bool hasBoundingBoxScale[MAX_ENTITIES];
extern bool hasCollisionState[MAX_ENTITIES];
extern bool hasPlayerTag[MAX_ENTITIES];
extern bool hasProp[MAX_ENTITIES];

// --- Init helpers ---

void add_name(Entity e, char* name);
void add_origin_offset(Entity e, Vector3 offset);
void add_position(Entity e, Vector3 pos);
void add_velocity(Entity e, Vector3 vel);
void add_acceleration(Entity e, Vector3 acc);
void add_friction(Entity e, float fric);
void add_movement_params(Entity e, MovementParams params);
void add_bounding_box(Entity e, BoundingBox bb);
void add_bounding_box_scale(Entity e, Vector3 bb_scale);
void add_collision_state(Entity e);
void add_camera_comp(Entity e, CameraComp cam);
void add_model_renderer(Entity e, ModelRenderer model_renderer);

#endif