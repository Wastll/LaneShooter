#include "raylib.h"
#include "assets.h"

static GameAssets assets;

#define VISUAL_PATH "assets/visual/"

Texture2D load_texture_nearest_neighbor(const char *path)
{
    Texture2D tex = LoadTexture(path);
    SetTextureFilter(tex, TEXTURE_FILTER_POINT);
    return tex;
}


void init_assets(void)
{
    assets.missing_texture = load_texture_nearest_neighbor(VISUAL_PATH "missing_texture.png");
    assets.missing_uv = load_texture_nearest_neighbor(VISUAL_PATH "missing_uv.png");

    assets.skybox = load_texture_nearest_neighbor(VISUAL_PATH "world/skybox.png");

    assets.player_placeholder = load_texture_nearest_neighbor(VISUAL_PATH "player/placeholder.png");
    
    assets.player_spritesheet_idle = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_idle.png");
    assets.player_spritesheet_walk = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_walk.png");
    assets.player_spritesheet_run = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_run.png");
    
    assets.texture_meadow = load_texture_nearest_neighbor(VISUAL_PATH "world/texture_meadow.png");
    
    assets.cube = LoadModel(VISUAL_PATH "world/cube.obj");
}

void unload_assets(void)
{
    UnloadTexture(assets.skybox);
    UnloadTexture(assets.player_placeholder);
    
    UnloadModel(assets.cube);
    UnloadTexture(assets.texture_meadow);
}

GameAssets *get_assets(void)
{
    return &assets;
}
