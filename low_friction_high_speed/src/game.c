#include "game.h"
#include "assets.h"
#include "systems.h"
#include "player.h"
#include "string.h"
#include "stdio.h"
#include "world.h"
#include "cam.h"

static RenderTexture2D target;

void init_game(int fb_w, int fb_h)
{
    init_assets();
    init_cam();
    init_world();
    init_player();
    // Fixed camera position (in cube units)

    target = LoadRenderTexture(fb_w, fb_h);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}

void update_game(void)
{
    float dt = GetFrameTime();
    update_physics(dt);
    update_cam(positions[1].x-positions[0].x);
    update_player();
}

void draw_framebuffer()
{
    int fb_w = target.texture.width;
    int fb_h = target.texture.height;

    BeginTextureMode(target);

    // --- 2D ---

    ClearBackground(PINK);
    draw_background(fb_w, fb_h);

    // --- 3D ---

    BeginMode3D(*get_cam());
    draw_lanes();
    DrawSphere(get_cam()->target, 0.05f, RED); // Camera target
    EndMode3D();

    EndTextureMode();
}

void draw_upscale()
{
    BeginDrawing();

    // --- 2D ---
    ClearBackground(BLACK);

    DrawTexturePro(
        target.texture,
        (Rectangle){0, 0, target.texture.width, -target.texture.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0}, 0.0f, WHITE);

    // --- 3D ---

    BeginMode3D(*get_cam());
    draw_player(get_cam());
    DrawSphere((Vector3){0,0,0},0.05f,RED); // Origin
    EndMode3D();

    draw_ui();

    EndDrawing();
}

// Will get moved later
void draw_ui(void)
{
    DrawText(TextFormat("%d FPS", GetFPS()), 10, 10, 20, PINK);
    int x = 10, y = GetScreenHeight()-100; // Screen position for text
    int spacing = 24;
    
    DrawText(TextFormat("POS: X %.2f  Y %.2f  Z %.2f", 
        positions[1].x, positions[1].y, positions[1].z), x, y, 20, GREEN);

    DrawText(TextFormat("VEL: X %.2f  Y %.2f  Z %.2f", 
        velocities[1].x, velocities[1].y, velocities[1].z), x, y + spacing, 20, YELLOW);

    DrawText(TextFormat("ACC: X %.2f  Y %.2f  Z %.2f", 
        accelerations[1].x, accelerations[1].y, accelerations[1].z), x, y + 2*spacing, 20, ORANGE);

}
