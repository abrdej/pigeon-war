//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_POWER_BULLET_H
#define PIGEONWAR_POWER_BULLET_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class power_bullet final : public straight_target_ability<2>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::power_bullet;
    }

private:
    void use(size_t index_on) override;

private:
    const int full_damage = 16;
    const int damage_with_power_bullet_effect = 4;
    const int duration_of_effect = 3;
};

#endif //PIGEONWAR_POWER_BULLET_H