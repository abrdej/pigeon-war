//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_WARRIOR_BLOW_H
#define PIGEONWAR_WARRIOR_BLOW_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class warrior_blow final : public neighboring_target_ability<>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::warrior_blow;
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

private:
    const std::uint32_t damage = 10;
    const std::uint32_t damage_per_factor = 2;
};


#endif //PIGEONWAR_WARRIOR_BLOW_H
