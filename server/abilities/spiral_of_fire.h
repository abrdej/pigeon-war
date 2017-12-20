//
// Created by abrde on 02.12.2017.
//

#ifndef PIGEONWAR_SPIRAL_OF_FIRE_H
#define PIGEONWAR_SPIRAL_OF_FIRE_H

#include "ability.h"
#include <vector>

class chopper;

class spiral_of_fire final : public ability
{
public:
    spiral_of_fire();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::spiral_of_fire;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range = 3;
    const int damage = 12;
    bool can_be_used{false};

    friend class chopper;
};

#endif //PIGEONWAR_SPIRAL_OF_FIRE_H
