#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class sword_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
    ADD_BITMAP_GETTER(sword_blow)
    DEFINE_DESC_ONE(sword_blow, damage)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage = 10;
};
