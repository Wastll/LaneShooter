#include "my_utils.h"
#include "raylib.h"
#include "raymath.h"

void DrawBoundingBoxEx(Entity e, Color color)
{
    if (!hasPosition[e] || !hasBoundingBox[e])
        return;

    BoundingBox box = bounding_boxes[e];
    Vector3 size = {
        box.max.x - box.min.x,
        box.max.y - box.min.y,
        box.max.z - box.min.z};

    Vector3 center = {
        box.min.x + size.x / 2.0f,
        box.min.y + size.y / 2.0f,
        box.min.z + size.z / 2.0f};

    ModelRenderer *mr = &model_renderers[e];

    center = Vector3Add(Vector3Add(center, positions[e]), mr->offset);

    if (hasBoundingBoxScale[e])
        DrawCubeWires(center, size.x * bounding_box_scales[e].x, size.y * bounding_box_scales[e].y, size.z * bounding_box_scales[e].z, color);
    else
        DrawCubeWires(center, size.x, size.y, size.z, color);
}

int sign(float num)
{
    if (num > 0)
        return 1;
    if (num < 0)
        return -1;
    return 0;
}

bool array_contains_int(const int *arr, size_t len, int value)
{
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] == value)
            return true;
    }
    return false;
}

static Entity find_player(void)
{
    for (Entity e = 0; e < MAX_ENTITIES; e++)
        if (entity_used[e] && hasPlayerTag[e])
            return e;

    return MAX_ENTITIES;
}

static Entity cached_player = MAX_ENTITIES;

Entity find_player_entity(void)
{
    if (cached_player == MAX_ENTITIES ||
        !entity_used[cached_player] ||
        !hasPlayerTag[cached_player])
    {
        cached_player = find_player();
    }
    return cached_player;
}