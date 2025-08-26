#include "utils.h"
#include "raymath.h"

void DrawBoundingBoxEx(Entity e, Color color){
    if(!hasPosition[e] || !hasBoundingBox[e]) return;

    BoundingBox box = bounding_boxes[e];
    Vector3 size = {
        box.max.x - box.min.x,
        box.max.y - box.min.y,
        box.max.z - box.min.z
    };

    Vector3 center = {
        box.min.x + size.x / 2.0f,
        box.min.y + size.y / 2.0f,
        box.min.z + size.z / 2.0f
    };

    center = Vector3Add(center, positions[e]);

    DrawCubeWires(center, size.x, size.y, size.z, color);
}