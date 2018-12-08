#pragma once

#include <abilities/ability.h>

class dragon_skin : public passive_ability {
public:
    explicit dragon_skin(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(dragon_skin)

    DEFINE_DESC_ONE(dragon_skin, magic_damage_reduction)

private:
    float magic_damage_reduction{0.25f};
};
