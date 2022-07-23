//
// Created by abrdej on 16.02.18.
//

#ifndef PIGEONWAR_FLAME_BURNING_H
#define PIGEONWAR_FLAME_BURNING_H

#include <turn_based/per_turn_usable.h>
#include <straight_target_ability.h>

class flame_burning final : public straight_target_ability<3>, protected per_turn_usable
{
public:
    explicit flame_burning(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "flame_burning";
    }

    DEFINE_DESC(flame_burning, damage, burn_magic_power)

private:
    void use(std::uint32_t index_on) override;

private:
    std::int32_t damage{10};
    std::int32_t burn_magic_power{4};
};


#endif //PIGEONWAR_FLAME_BURNING_H
