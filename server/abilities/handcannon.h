//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDCANNON_H
#define PIGEONWAR_HANDCANNON_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class handcannon final : public straight_target_ability<3>,
                         per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::handcannon;
    }

private:
    void use(sf::Uint64 index_on) override;

private:
    const sf::Int32 damage = 8;
    const sf::Int32 bonus_damage = 5;
    bool used{false};
};

#endif //PIGEONWAR_HANDCANNON_H
