//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H
#define PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H

#include "ability.h"
#include "core/states.h"
#include "core/game_controller.h"

template <target_types TargetType = target_types::enemy,
		bool Available = false>
class neighboring_target_ability : public active_ability {
public:
	void prepare(std::uint32_t for_index) override {
		game_control().selected_index_ = for_index;
		board_helper::neighboring_fields(for_index, game_control().possible_movements_, available);

		game_control().actual_targeting_type_ = target_type;
		game_control().wait_for_action([this](std::uint32_t index)
												  {
													  return use(index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
protected:
	const target_types target_type{TargetType};
	const bool available{Available};
};

#endif //PIGEONWAR_NEIGHBORING_TARGET_ABILITY_H
