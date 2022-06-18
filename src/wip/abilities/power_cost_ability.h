#pragma once

#include <components/power_field.h>
#include <turn_based/managers/entity_manager.h>
#include <cstdint>

inline bool use_ability_at_the_expense_of_power(std::uint32_t entity_id, std::int32_t cost) {
  auto& power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;
  if (power < cost) {
    return false;
  } else {
    power -= cost;
    sender::send(make_action_message("change_power", entity_id, -cost));
    return true;
  }
}
