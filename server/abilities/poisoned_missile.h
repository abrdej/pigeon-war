//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_POISONED_MISSILE_H
#define PIGEONWAR_POISONED_MISSILE_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class poisoned_missile final : public path_target_ability<4>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::poisoned_missile;
    }

private:
    void use(size_t index_on);

private:
    const int damage{6};
    const int poison_power{3};
    const int poison_last{3};
};

#endif //PIGEONWAR_POISONED_MISSILE_H
