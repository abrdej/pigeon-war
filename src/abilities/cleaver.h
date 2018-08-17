#pragma once

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class cleaver final : public neighboring_target_ability<>, per_turn_usable
{
public:
    explicit cleaver(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "cleaver";
    }
    ability_types type() const override {
        return ability_types::offensive;
    }

    DEFINE_DESC_ONE(cleaver, damage)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::uint32_t entity_id;
    const std::int32_t damage = 8;
    const std::int32_t power_charge = 5;
};
