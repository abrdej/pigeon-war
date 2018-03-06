//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_CASTER_TARGET_ABILITY_H
#define PIGEONWAR_CASTER_TARGET_ABILITY_H

#include "ability.h"
#include "common/states.h"
#include "core/states_controller.h"

class caster_target_ability : public active_ability {
public:
	void prepare(std::uint32_t for_index) {
		states::state_controller::actual_state_ = states::states_types::wait_for_action;
		states::state_controller::possible_movements_.clear();
		states::state_controller::possible_movements_.push_back(for_index);
		states::state_controller::actual_targeting_type_ = target_types::caster;
		states::state_controller::wait_for_action([this](std::uint32_t index)
												  {
													  return use(index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
};

#endif //PIGEONWAR_CASTER_TARGET_ABILITY_H
