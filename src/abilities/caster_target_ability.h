//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_CASTER_TARGET_ABILITY_H
#define PIGEONWAR_CASTER_TARGET_ABILITY_H

#include "ability.h"
#include "core/states.h"
#include "core/game_controller.h"

class caster_target_ability : public active_ability {
public:
	void prepare(std::uint32_t for_index) {
		game_control().actual_state_ = states_types::wait_for_action;
		game_control().possible_movements_.clear();
		game_control().possible_movements_.push_back(for_index);
		game_control().actual_targeting_type_ = target_types::caster;
		game_control().wait_for_action([this](std::uint32_t index)
												  {
													  return use(index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
};

#endif //PIGEONWAR_CASTER_TARGET_ABILITY_H
