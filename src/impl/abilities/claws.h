#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class claws final : public neighboring_target_ability<>, per_turn_usable {
public:
    ADD_BITMAP_GETTER(claws)

    ABILITY_TYPE(offensive)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t range = 1;
    const std::int32_t damage = 4;
};
