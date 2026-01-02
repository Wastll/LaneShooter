#include "utils.h"
#include "raymath.h"
#include "components.h"

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

    center = Vector3Add(Vector3Add(center, positions[e]), origin_offsets[e]);

    if(hasBoundingBoxScale[e]) DrawCubeWires(center, size.x*bounding_box_scales[e].x, size.y*bounding_box_scales[e].y, size.z*bounding_box_scales[e].z, color);
    else DrawCubeWires(center, size.x, size.y, size.z, color);
}

int sign(float num){
if (num > 0) return 1;
if (num < 0) return -1;
return 0;
}