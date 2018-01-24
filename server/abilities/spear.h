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
    spear(std::uint32_t id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::spear;
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

private:
    static const std::int32_t range = 1;
    static const std::int32_t damage = 6;
    const std::int32_t additional_damage{6};
    std::int32_t accumulated_damage{0};
    std::uint32_t entity_id;
};


#endif //PIGEONWAR_SPEAR_H
