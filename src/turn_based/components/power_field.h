#pragma once

#include <cstdint>

#include <turn_based/board.h>
#include <turn_based/turn_system.h>
#include <turn_based/sender.h>
#include <turn_based/messages/messages_makers.h>

struct power_filed : turn_callback_helper {
  explicit power_filed(std::uint32_t entity_id, std::int32_t initial_power,
                       std::int32_t charging_power_amount, std::int32_t max_power = 0)
      : power(initial_power), charging_power_amount(charging_power_amount), max_power(max_power) {
    if (charging_power_amount != 0) {
      after_player_turn(entity_id, [this, entity_id]() {
        auto power_to_charge = std::min(this->max_power - this->power, this->charging_power_amount);
        this->power += power_to_charge;
        sender::send(make_action_message("change_power", entity_id, power_to_charge));
      });
    }
  }
  std::int32_t power;
  std::int32_t charging_power_amount;
  std::int32_t max_power;
};

inline std::int32_t change_power(power_filed& x, std::int32_t amount) {
  auto past_power = x.power;
  x.power = std::min(x.power + amount, x.max_power);
  x.power = std::max(x.power, 0);
  return x.power - past_power;
}
