//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_SPEAR_H
#define PIGEONWAR_SPEAR_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class spear final : public straight_target_ability<1>, per_turn_usable
{
public:
    spear(sf::Uint64 id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::spear;
    }

    std::string hint() const override;

private:
    void use(sf::Uint64 index_on) override;

private:
    static const sf::Int32 range = 1;
    static const sf::Int32 damage = 6;
    const sf::Int32 additional_damage{4};
    sf::Int32 accumulated_damage{0};
    sf::Uint64 entity_id;
};


#endif //PIGEONWAR_SPEAR_H
