//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_STONE_SKIN_H
#define PIGEONWAR_STONE_SKIN_H

#include "ability.h"

class stone_skin : public passive_ability {
public:
    explicit stone_skin(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::stone_skin;
    }

    DEFINE_DESC(stone_skin, damage_reduction, reduction_increase_amount)

private:
    int damage_reduction{0};
    int reduction_increase_amount{1};
};

#endif //PIGEONWAR_STONE_SKIN_H
