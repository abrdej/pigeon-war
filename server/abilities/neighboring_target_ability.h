//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H
#define PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H

#include "ability.h"
#include "common/states.h"
#include "core/states_controller.h"

template <states::target_types TargetType = states::target_types::enemy,
		bool Available = false>
class neighboring_target_ability : public ability {
public:
	void prepare(sf::Uint64 for_index) override {
		states::state_controller::selected_index_ = for_index;
		board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, available);

		states::state_controller::actual_targeting_type_ = target_type;
		states::state_controller::wait_for_action([this](sf::Uint64 index)
												  {
													  return use(index);
												  });
	}
	virtual void use(sf::Uint64 use_on_index) = 0;
protected:
	const states::target_types target_type{TargetType};
	const bool available{Available};
};

#endif //PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H
