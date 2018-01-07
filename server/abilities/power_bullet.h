//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_POWER_BULLET_H
#define PIGEONWAR_POWER_BULLET_H

#include "ability.h"
#include "core/turn.h"

class power_bullet final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    power_bullet();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::power_bullet;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range = 3;
    const int damage_per_turn = 10;
    const int turn_for_additional_damage = 3;
    bool used{false};
};

#endif //PIGEONWAR_POWER_BULLET_H
