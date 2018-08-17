#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class warrior_blow final : public neighboring_target_ability<>, per_turn_usable
{
public:
    explicit warrior_blow(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "warrior_blow";
    }

    DEFINE_DESC_ONE(warrior_blow, damage)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::uint32_t entity_id;
    const std::int32_t damage = 10;
    const std::int32_t damage_per_factor = 2;
};
