#include "game.h"
#include "assets.h"
#include "systems.h"
#include "player.h"
#include "world.h"
#include "cam.h"
#include "keyhandler.h"
#include "anim_defs.h"
#include "debug_system.h"

static RenderTexture2D target;

void init_game(int fb_w, int fb_h)
{
    init_assets();
    init_animation_defs();
    init_world();
    init_player();
    init_cam();

    target = LoadRenderTexture(fb_w, fb_h);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}

void update_game(void)
{
    float dt = GetFrameTime();
    poll_keys();
    input_system();
    update_physics(dt);
    camera_system();
    animation_system(dt);
}

void draw_framebuffer()
{
    BeginTextureMode(target);

    // --- 2D ---
    ClearBackground(PINK);
    draw_background(target.texture.width, target.texture.height);

    // --- 3D ---
    BeginMode3D(*get_cam());
    render_models();
    render_multi_models();

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
        (Rectangle){0, 0, 1920, 1080},
        (Vector2){0, 0}, 0.0f, WHITE);

    // --- 3D ---
    BeginMode3D(*get_cam());

    // Redraw lanes in upscaled version to get z-ordering
    rlEnableDepthTest();
    glColorMask(0, 0, 0, 0);
    render_models();
    render_multi_models();
    glColorMask(1, 1, 1, 1);

    render_billboards(get_cam());
    debug_info_3d();

    EndMode3D();

    debug_info_2d();

    EndDrawing();
}