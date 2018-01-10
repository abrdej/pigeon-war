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
    spear(std::size_t id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::spear;
    }

private:
    void use(size_t index_on) override;

private:
    static const int range = 1;
    static const int damage = 6;
    bool used{false};
    int accumulated_damage{0};
    std::size_t entity_id;
};


#endif //PIGEONWAR_SPEAR_H
