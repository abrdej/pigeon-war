//
// Created by abrde on 02.12.2017.
//

#ifndef PIGEONWAR_SPIRAL_OF_FIRE_H
#define PIGEONWAR_SPIRAL_OF_FIRE_H

#include "straight_target_ability.h"
#include <vector>

class chopper;

class spiral_of_fire final : public straight_target_ability<3, states::target_types::enemy, true>
{
public:
    spiral_of_fire();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::spiral_of_fire;
    }

private:
    void use(sf::Uint64 index_on) override;

private:
    const sf::Int32 damage = 12;
    bool can_be_used{false};

    friend class chopper;
};

#endif //PIGEONWAR_SPIRAL_OF_FIRE_H
