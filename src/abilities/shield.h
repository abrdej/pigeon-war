#pragma once

#include <abilities/ability.h>

class shield : public passive_ability {
public:
    explicit shield(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(shield)

    DEFINE_DESC_ZERO(shield)

private:
    const float range_attack_reduction{0.5f};
};
