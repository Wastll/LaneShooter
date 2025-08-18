#include "game.h"
#include "assets.h"
#include "systems.h"
#include "player.h"
#include "string.h"
#include "stdio.h"
#include "world.h"

static Camera3D camera;
static RenderTexture2D target;

void init_game(int fb_w, int fb_h)
{
    init_assets();
    init_player();
    init_world();

    // Fixed camera position (in cube units)
    camera = (Camera3D){0};
    camera.position = (Vector3){0, 4.5f, 3.5f};
    camera.target = (Vector3){0, 0.0f, -2.5f};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 60.0f;

    camera.projection = CAMERA_PERSPECTIVE;

    target = LoadRenderTexture(fb_w, fb_h);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}

void update_game(void)
{
    float dt = GetFrameTime();
    update_physics(dt);
    update_player();

    // Straight look at origin (0,0,0) for alignment
    if(IsKeyDown(KEY_A)){
        camera.position = (Vector3){0, 0.0f, 5.0f};
        camera.target = (Vector3){0, 0.0f, 0.0f};
    }
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

    BeginMode3D(camera);
    draw_lanes();
    DrawSphere(camera.target, 0.05f, RED); // Camera target
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

    BeginMode3D(camera);
    draw_player(&camera);
    DrawSphere((Vector3){0,0,0},0.05f,RED); // Origin
    EndMode3D();

    draw_ui();

    EndDrawing();
}

// Will get moved later
void draw_ui(void)
{
    DrawText(TextFormat("%d FPS", GetFPS()), 10, 10, 20, PINK);
}
