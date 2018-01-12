//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_ARMOR_H
#define PIGEONWAR_ARMOR_H

#include "ability.h"

class armor : public passive_ability {
public:
    explicit armor(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::armor;
    }

    std::string hint() const override;

private:
    int max_damage{6};
};


#endif //PIGEONWAR_ARMOR_H
