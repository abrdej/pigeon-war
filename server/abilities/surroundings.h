//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SURROUNDINGS_H
#define PIGEONWAR_SURROUNDINGS_H

#include "ability.h"

class surroundings : public passive_ability {
public:
    explicit surroundings(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::surroundings;
    }

private:
    int damage_reduction{3};
    int min_damage{3};
};

#endif //PIGEONWAR_SURROUNDINGS_H
