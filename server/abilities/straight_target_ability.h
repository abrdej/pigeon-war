//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H
#define PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H

#include "ability.h"
#include "common/states.h"
#include "core/states_controller.h"

template <int Range,
		states::target_types TargetType = states::target_types::enemy,
		bool SkipObstacles = false>
class straight_target_ability : public ability {
public:
	void prepare(size_t index) override {
		states::state_controller::selected_index_ = index;

		board_helper::calc_straight(index, states::state_controller::possible_movements_,
									states::state_controller::possible_movements_costs_,
									range, skip_obstacles);

		states::state_controller::actual_targeting_type_ = target_type;
		states::state_controller::wait_for_action([this](size_t used_on_index)
												  {
													  return use(used_on_index);
												  });
	}
	virtual void use(std::size_t use_on_index) = 0;
protected:
	int range{Range};
	const states::target_types target_type{TargetType};
	const bool skip_obstacles{SkipObstacles};
};


#endif //PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H
