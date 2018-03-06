//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_PATH_TARGET_ABILITY_H
#define PIGEONWAR_PATH_TARGET_ABILITY_H

#include "ability.h"
#include "common/states.h"
#include "core/states_controller.h"

template <std::int32_t Range,
		target_types TargetType = target_types::enemy,
		bool AllFields = true>
class path_target_ability : public active_ability {
public:
	void prepare(std::uint32_t for_index) override {

		states::state_controller::selected_index_ = for_index;

		path_finder path_finder(all_fields);
		path_finder.calc(for_index);
		path_finder.get_possible_movements(states::state_controller::possible_movements_,
										   states::state_controller::possible_movements_costs_,
										   range);

		states::state_controller::actual_targeting_type_ = target_type;
		states::state_controller::wait_for_action([this](std::uint32_t index)
												  {
													  return use(index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
protected:
	std::int32_t range{Range};
	const target_types target_type{TargetType};
	const bool all_fields{AllFields};
};

#endif //PIGEONWAR_PATH_TARGET_ABILITY_H
