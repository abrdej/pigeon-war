//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_ARMOR_H
#define PIGEONWAR_ARMOR_H

#include "ability.h"

class armor : public passive_ability {
public:
    explicit armor(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::armor;
    }

    std::string hint() const override;

private:
    sf::Int32 max_damage{6};
};


#endif //PIGEONWAR_ARMOR_H
