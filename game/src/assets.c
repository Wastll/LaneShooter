#include "raylib.h"
#include "assets.h"

static GameAssets assets;

#define VISUAL_PATH "assets/visual/"

void init_assets(void)
{
    assets.skybox = LoadTexture(VISUAL_PATH "world/skybox.png");
    SetTextureFilter(assets.skybox, TEXTURE_FILTER_POINT);

    assets.player_placeholder = LoadTexture(VISUAL_PATH "player/placeholder.png");
    SetTextureFilter(assets.player_placeholder, TEXTURE_FILTER_POINT);

    assets.texture_meadow = LoadTexture(VISUAL_PATH "world/texture_meadow.png");
    SetTextureFilter(assets.texture_meadow, TEXTURE_FILTER_POINT);
    
    assets.cube = LoadModel(VISUAL_PATH "world/cube.obj");
    assets.cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = assets.texture_meadow;

}

void unload_assets(void)
{
    UnloadTexture(assets.skybox);
    UnloadTexture(assets.player_placeholder);
    UnloadTexture(assets.texture_meadow);

    UnloadModel(assets.cube);
}

GameAssets* get_assets(void) {
    return &assets;
}
