#include "world_props.h"
#include "assets.h"

static PropComp init_prop(Entity e, ModelRenderer mr, Vector3 pos, bool breakable, float hardness, Vector3 bb_scale)
{
    hasProp[e] = true;
    add_model_renderer(e, mr);
    add_position(e, pos);
    add_bounding_box(e, GetModelBoundingBox(*mr.model));
    if (bb_scale.x != 1.f || bb_scale.y != 1.f || bb_scale.z != 1.f)
        add_bounding_box_scale(e, bb_scale);
    add_collision_state(e);

    return (PropComp){ e, breakable, hardness };
}

void init_props(void)
{
    Vector3 default_prop_offset = {0.5f, -0.5f, -0.5f};
    Vector3 default_bb_scale = {1.f, 1.f, 1.f};

    ModelRenderer mr_meadow=(ModelRenderer){&get_assets()->cube_meadow, default_prop_offset, 1.f, WHITE};
    ModelRenderer mr_crate=(ModelRenderer){&get_assets()->cube_crate, default_prop_offset, 1.f, WHITE};
    ModelRenderer mr_barrel=(ModelRenderer){&get_assets()->cylinder_barrel, default_prop_offset, 1.f, WHITE};
    ModelRenderer mr_tree=(ModelRenderer){&get_assets()->tree, default_prop_offset, 1.f, WHITE};

    Entity floating_meadow = create_entity();
    props[floating_meadow] = init_prop(floating_meadow,mr_meadow, (Vector3){4, 3, -2}, false, 1.f, default_bb_scale);

    Entity crate = create_entity();
    props[crate] = init_prop(crate,mr_crate, (Vector3){4, 1, -1}, false, 1.f, default_bb_scale);

    Entity barrel = create_entity();
    props[barrel] = init_prop(barrel,mr_barrel, (Vector3){2, 1, -1}, false, 1.f,(Vector3){0.9f, 1.f, 0.9f});

    Entity tree = create_entity();
    props[tree] = init_prop(tree,mr_tree, (Vector3){2, 2, -3}, false, 1.f, (Vector3){0.4f, 1.f, 0.4f});
}