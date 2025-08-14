#include "raylib.h"

#define lane_w 64
#define lane_h 5

Color lane_depth_tint[lane_h];

void drawLanesModel(float platform_shift, Model model)
{
    for (int i = 0; i < lane_w; i++)
        for (int j = 0; j < lane_h; j++)
        {
            Vector3 pos1 = (Vector3){i * 16 + platform_shift, 24, -j * 16};

            DrawModel(model, pos1, 16, lane_depth_tint[j]);
        }
}

Color get_player_depth_tint(float lane_edge_z, float player_z)
{
    const int player_depth_darkness_lvl = 22;
    return (Color){255 - (lane_edge_z - player_z) * player_depth_darkness_lvl, 255 - (lane_edge_z - player_z) * player_depth_darkness_lvl, 255, 255};
}

int main(void)
{
    // Frame buffer dimension
    const int renderWidth = 320;
    const int renderHeight = 180;

    // Full HD - 1920 x 1080
    const int screenWidth = renderWidth * 6;
    const int screenHeight = renderHeight * 6;

    Camera3D camera = {0};
    camera.position = (Vector3){512, 110, 82.0f};
    camera.target = (Vector3){512, -312.0f, -512.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 58.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Player component init
    float platform_shift = 0.0f;
    float player_z = camera.position.z - 1.5f;

    for (int i = 0; i < lane_h; i++)
    {
        const int lane_depth_darkness_lvl = 18;
        lane_depth_tint[i] = (Color){255 - lane_depth_darkness_lvl * i, 255 - lane_depth_darkness_lvl * i, 255, 255};
    }

    InitWindow(screenWidth, screenHeight, "Lane Shooter - Perspective Prototype");

    RenderTexture2D target = LoadRenderTexture(renderWidth, renderHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    Model grassBlock = LoadModel("assets/grass_block.obj");
    Texture2D texture_grass_block = LoadTexture("assets/texture_grass_block.png");
    grassBlock.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_grass_block;
    SetTextureFilter(texture_grass_block, TEXTURE_FILTER_POINT);

    SetTargetFPS(60);
    ToggleFullscreen();
    SetWindowMonitor(1);

    Texture2D texture_player = LoadTexture("assets/walk_frame.png");
    SetTextureFilter(texture_player, TEXTURE_FILTER_POINT);

    while (!WindowShouldClose())
    {
        // -------- Controls ----------

        float moveSpeed = 1.0f;
        float fovSpeed = 0.5f;

        if (IsKeyDown(KEY_D))
            platform_shift -= moveSpeed;
        if (IsKeyDown(KEY_A))
            platform_shift += moveSpeed;

        if (IsKeyDown(KEY_W))
            player_z -= 0.02f;
        if (IsKeyDown(KEY_S))
            player_z += 0.02f;

        if (IsKeyDown(KEY_E))
            camera.target.y += moveSpeed;
        if (IsKeyDown(KEY_Q))
            camera.target.y -= moveSpeed;
        
        // Target x will be fixed in game
        if (IsKeyDown(KEY_LEFT))
            camera.target.x -= moveSpeed;
        if (IsKeyDown(KEY_RIGHT))
            camera.target.x += moveSpeed;

        if (IsKeyDown(KEY_F))
            camera.fovy += fovSpeed;
        if (IsKeyDown(KEY_J))
            camera.fovy -= fovSpeed;

        // -------- Render to frame buffer ----------

        BeginTextureMode(target);

        ClearBackground((Color){100, 149, 237, 255});

        BeginMode3D(camera);
        drawLanesModel(platform_shift, grassBlock);
        EndMode3D();

        EndTextureMode();

        // -------- Upscaled ----------

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            target.texture,
            (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, // Flip vertically when drawing render texture
            (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
            (Vector2){0, 0}, 0.0f, WHITE);

        // Upscaled 3D Mode - avoid scaling artifacts
        BeginMode3D(camera);
        Vector3 pos = {lane_w * 0.5 * 16, (110 - 1), (player_z)};
        DrawBillboard(camera, texture_player, pos, 0.6, get_player_depth_tint(camera.position.z, player_z)); // size in world units
        EndMode3D();

        DrawText(TextFormat("Pos: %.1f %.1f %.1f", camera.position.x, camera.position.y, camera.position.z), 10, 6, 20, WHITE);
        DrawText(TextFormat("Target: %.1f %.1f %.1f", camera.target.x, camera.target.y, camera.target.z), 10, 28, 20, WHITE);
        DrawText(TextFormat("FOV: %.1f", camera.fovy), 10, 50, 20, WHITE);

        DrawFPS(screenWidth - 80, 10);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    UnloadTexture(texture_player);
    UnloadTexture(texture_grass_block);

    CloseWindow();
    return 0;
}
