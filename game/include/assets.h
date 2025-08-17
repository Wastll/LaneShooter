#include "raylib.h"

#ifndef ASSETS_H
#define ASSETS_H

typedef struct {
    Texture2D skybox;
    Texture2D player_placeholder;
    
    Texture2D texture_meadow;
    
    Model cube;

} GameAssets;

void init_assets(void);
void unload_assets(void);

GameAssets* get_assets(void);

#endif
