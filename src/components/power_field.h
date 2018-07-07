//
// Created by abrde on 20.12.2017.
//

#ifndef PIGEONWAR_MAGIC_POWER_MANAGER_H
#define PIGEONWAR_MAGIC_POWER_MANAGER_H

#include <cstdint>
#include "core/turn_system.h"
#include "core/board.h"
#include "sender.h"

struct power_filed : turn_callback_helper {
	explicit power_filed(std::uint32_t entity_id,
									   std::int32_t initial_power,
									   std::int32_t charging_power_amount,
									   std::int32_t max_power = 0)
			: power(initial_power),
			  charging_power_amount(charging_power_amount),
			  max_power(max_power) {

        if (charging_power_amount != 0) {
            after_player_turn(entity_id, [this, entity_id]() {
				auto power_to_charge = std::min(this->max_power - this->power, this->charging_power_amount);
                this->power += power_to_charge;
				sender::send(make_action_message("change_power",
												 game::get<board>().index_for(entity_id),
												 power_to_charge));
            });
        }
	}
	std::int32_t power;
	std::int32_t charging_power_amount;
	std::int32_t max_power;
};

#endif //PIGEONWAR_MAGIC_POWER_MANAGER_H
