#pragma once

#include <abilities/ability.h>

class shield : public passive_ability {
public:
    explicit shield(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "shield";
    }

    DEFINE_DESC_ZERO(shield)

private:
    const float range_attack_reduction{0.5f};
};
