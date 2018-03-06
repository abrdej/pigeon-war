//
// Created by abrdej on 16.02.18.
//

#ifndef PIGEONWAR_MORTAR_THROWER_H
#define PIGEONWAR_MORTAR_THROWER_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class mortar_thrower final : public path_target_ability<4>,
                             per_turn_usable
{
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::change_rocket_type;
    }

    DEFINE_DESC(mortar_thrower, base_damage, rocket_change_bonus, range)

    bool was_used() const {
        return used;
    }
    void set_used() {
        used = true;
    }

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t base_damage = 7;
    const std::int32_t rocket_change_bonus = 3;
};

#endif //PIGEONWAR_MORTAR_THROWER_H
