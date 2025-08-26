#include "game.h"
#include "assets.h"
#include "systems.h"
#include "player.h"
#include "string.h"
#include "stdio.h"
#include "world.h"
#include "cam.h"
#include "rlgl.h"
#include <GL/gl.h>

static RenderTexture2D target;
static Entity e_cam = 0;
static Entity e_player = 1;

void init_game(int fb_w, int fb_h)
{
    init_assets();
    init_world();
    init_player();
    init_cam();

    target = LoadRenderTexture(fb_w, fb_h);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}

void update_game(void)
{
    float dt = GetFrameTime();
    update_physics(dt);
    update_player();
    update_world(dt);
    update_cam(positions[e_player].x - positions[e_cam].x);
}

void draw_framebuffer()
{
    BeginTextureMode(target);

    // --- 2D ---
    ClearBackground(PINK);
    draw_background(target.texture.width, target.texture.height);

    // --- 3D ---
    BeginMode3D(*get_cam());
    draw_world();
    DrawSphere(get_cam()->target, 0.05f, RED); // Camera target marker
    EndMode3D();
    
    EndTextureMode();
}

void draw_upscale()
{
    BeginDrawing();
    // --- Draw frame buffer to screen ---
    ClearBackground(PINK);

    DrawTexturePro(
        target.texture,
        (Rectangle){0, 0, target.texture.width, -target.texture.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0}, 0.0f, WHITE);

    // --- 3D ---
    BeginMode3D(*get_cam());

    //Redraw lanes in upscaled version to get z-ordering
    rlEnableDepthTest();
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    draw_world();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    draw_player(get_cam());
    DrawSphere((Vector3){0, 0, 0}, 0.05f, RED); // Origin marker
    EndMode3D();

    draw_ui();

    EndDrawing();
}

// Will get moved later
void draw_ui(void)
{
    DrawText(TextFormat("%d FPS", GetFPS()), 10, 10, 20, PINK);
    int x = 10, y = GetScreenHeight() - 100;
    int spacing = 24;

    DrawText(TextFormat("POS: X %.2f  Y %.2f  Z %.2f",
                        positions[e_player].x, positions[e_player].y, positions[e_player].z),
             x, y, 20, GREEN);

    DrawText(TextFormat("VEL: X %.2f  Y %.2f  Z %.2f",
                        velocities[e_player].x, velocities[e_player].y, velocities[e_player].z),
             x, y + spacing, 20, YELLOW);

    DrawText(TextFormat("ACC: X %.2f  Y %.2f  Z %.2f",
                        accelerations[e_player].x, accelerations[e_player].y, accelerations[e_player].z),
             x, y + 2 * spacing, 20, ORANGE);
}
