//
// Created by abrdej on 06.02.18.
//

#ifndef PIGEONWAR_POWER_COST_ABILITY_H
#define PIGEONWAR_POWER_COST_ABILITY_H

#include <cstdint>
#include <managers/entity_manager.h>
#include <components/power_field.h>

inline bool use_ability_at_the_expense_of_power(std::uint32_t entity_id,
                                                std::int32_t cost) {
    auto& power = entity_manager::get(entity_id).get<power_filed>()->power;
    if (power < cost) {
        return false;
    } else {
        power -= cost;
        return true;
    }
}


#endif //PIGEONWAR_POWER_COST_ABILITY_H
