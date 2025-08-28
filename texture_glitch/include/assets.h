#include "raylib.h"
#include "components.h"

#ifndef ASSETS_H
#define ASSETS_H

typedef struct {
    Texture2D missing_texture;
    Texture2D missing_uv;

    Texture2D skybox;
    Texture2D texture_meadow;
    
    Texture2D player_placeholder;
    Texture2D player_spritesheet_idle;
    Texture2D player_spritesheet_walk;
    Texture2D player_spritesheet_run;

    Model cube;

} GameAssets;

Texture2D load_texture_nearest_neighbor(const char* path);
void init_assets(void);
void unload_assets(void);

GameAssets* get_assets(void);

#endif
