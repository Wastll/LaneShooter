#include "assets.h"

static GameAssets assets;

#define VISUAL_PATH "assets/visual/"

static Texture2D missing_tex = {0};

static Texture2D create_missing_texture(void)
{
    Image img = GenImageColor(2, 2, MAGENTA);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

static Texture2D get_missing_texture(void)
{
    if (missing_tex.id == 0)
        missing_tex = create_missing_texture();
    return missing_tex;
}

static Model create_missing_cube(void)
{
    Texture2D tex = get_missing_texture();
    Mesh mesh = GenMeshCube(1, 1, 1);
    Model m = LoadModelFromMesh(mesh);
    if (m.materialCount > 0)
        m.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    return m;
}

Texture2D load_texture_nearest_neighbor(const char *path)
{
    Texture2D tex = LoadTexture(path);
    if(tex.id == 0) tex = get_missing_texture();
    SetTextureFilter(tex, TEXTURE_FILTER_POINT);
    return tex;
}

static Model LoadModelWithTextureSafe(const char *path, Texture2D tex) {
    Model m = LoadModel(path);
    if(m.meshCount==0) return create_missing_cube();
    m.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    return m;
}

static Model LoadCubeWithTexture(Texture2D tex) {
    return LoadModelWithTextureSafe(VISUAL_PATH "world/cube.obj", tex);
}

static Model LoadCylinderWithTexture(Texture2D tex) {
    return LoadModelWithTextureSafe(VISUAL_PATH "world/cylinder.obj", tex);
}


void init_assets(void)
{
    assets.skybox = load_texture_nearest_neighbor(VISUAL_PATH "world/skybox.png");
    
    assets.player_placeholder = load_texture_nearest_neighbor(VISUAL_PATH "player/placeholder.png");
    
    assets.player_spritesheet_idle = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_idle.png");
    assets.player_spritesheet_walk = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_walk.png");
    assets.player_spritesheet_run = load_texture_nearest_neighbor(VISUAL_PATH "player/spritesheet_run.png");
    
    assets.missing_uv = load_texture_nearest_neighbor(VISUAL_PATH "missing_uv.png");
    assets.texture_meadow = load_texture_nearest_neighbor(VISUAL_PATH "world/texture_meadow.png");
    assets.texture_crate = load_texture_nearest_neighbor(VISUAL_PATH "world/texture_crate.png");
    assets.texture_barrel = load_texture_nearest_neighbor(VISUAL_PATH "world/texture_barrel.png");      
    assets.texture_tree = load_texture_nearest_neighbor(VISUAL_PATH "world/texture_tree_test.png");

    assets.cube = LoadCubeWithTexture(assets.missing_uv);
    assets.cube_meadow = LoadCubeWithTexture(assets.texture_meadow);
    assets.cube_crate = LoadCubeWithTexture(assets.texture_crate);
    assets.cylinder_barrel = LoadModelWithTextureSafe(VISUAL_PATH "world/bulge_barrel.obj", assets.texture_barrel);
    assets.tree = LoadModelWithTextureSafe(VISUAL_PATH "world/tree_test.obj", assets.texture_tree);
}

void unload_assets(void)
{
    UnloadTexture(assets.skybox);
    UnloadTexture(assets.player_placeholder);
    UnloadTexture(assets.player_spritesheet_idle);
    UnloadTexture(assets.player_spritesheet_walk);
    UnloadTexture(assets.player_spritesheet_run);
    UnloadTexture(assets.missing_uv);
    UnloadTexture(assets.texture_meadow);
    UnloadTexture(assets.texture_crate);
    UnloadTexture(assets.texture_barrel);

    UnloadModel(assets.cube);
    UnloadModel(assets.cube_meadow);
    UnloadModel(assets.cube_crate);
    UnloadModel(assets.cylinder_barrel);

    if (missing_tex.id != 0) UnloadTexture(missing_tex);
}
GameAssets *get_assets(void)
{
    return &assets;
}
