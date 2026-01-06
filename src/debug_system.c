#include "debug_system.h"
#include "raylib.h"
#include "raymath.h"
#include "my_utils.h"

bool show_bounding_boxes = false;

void debug_info_2d()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, YELLOW);

    Entity e = find_player_entity();
    if (e == MAX_ENTITIES)
        return;

    Vector3 pos = positions[e];
    Vector3 vel = velocities[e];
    Vector3 acc = accelerations[e];

    DrawText(TextFormat("PPos: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z),
             10, GetScreenHeight() - 60, 20, GREEN);
    DrawText(TextFormat("PVel: %.2f, %.2f, %.2f", vel.x, vel.y, vel.z),
             10, GetScreenHeight() - 40, 20, YELLOW);
    DrawText(TextFormat("PAcc: %.2f, %.2f, %.2f", acc.x, acc.y, acc.z),
             10, GetScreenHeight() - 20, 20, ORANGE);
}

void debug_info_3d()
{
    DrawSphere((Vector3){0, 0, 0}, 0.05f, YELLOW);
    for (Entity e = 0; e < MAX_ENTITIES; e++)
    {
        if (!entity_used[e])
            continue;

        if (hasBoundingBox[e]&&show_bounding_boxes)
        {
            Color c = hasPlayerTag[e] ? GREEN : RED;
            DrawBoundingBoxEx(e, c);
        }

        if (hasCameraComp[e]) DrawSphere(cameras[e].cam.target, 0.05f, YELLOW);
    }
}

void debug_bb_toggle(void)
{
    show_bounding_boxes = !show_bounding_boxes;
}