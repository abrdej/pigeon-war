//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_POWER_BULLET_H
#define PIGEONWAR_POWER_BULLET_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class power_bullet final : public straight_target_ability<3>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::power_bullet;
    }

private:
    void use(size_t index_on) override;
    void play_animation(size_t from_index, size_t to_index);

private:
    const int damage_per_turn = 10;
    const int turn_for_additional_damage = 3;
    bool used{false};
};

#endif //PIGEONWAR_POWER_BULLET_H
