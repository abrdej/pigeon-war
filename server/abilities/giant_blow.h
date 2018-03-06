//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_BLOW_H
#define PIGEONWAR_GIANT_BLOW_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class giant_blow final : public neighboring_target_ability<>, per_turn_usable
{
public:
    ~giant_blow() final;

    bitmap_key get_bitmap_key() const override {
        return (counter == 2) ? bitmap_key::giant_blow_special : bitmap_key::giant_blow;
    }

    DEFINE_DESC_ONE(giant_blow, damage)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage{8};
    std::int32_t counter{0};
    std::int32_t duration_of_giant_only_target = 1;
    std::uint32_t enemy_with_effect{std::numeric_limits<std::uint32_t>::max()};
};

#endif //PIGEONWAR_GIANT_BLOW_H
