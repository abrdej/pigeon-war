//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H
#define PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H

#include "ability.h"
#include "core/states.h"
#include "core/game_controller.h"

template <std::int32_t Range,
		target_types TargetType = target_types::enemy,
		bool SkipObstacles = false>
class straight_target_ability : public active_ability {
public:
	void prepare(std::uint32_t index) override {
		game_control().selected_index_ = index;

		board_helper::calc_straight(index, game_control().possible_movements_,
									game_control().possible_movements_costs_,
									range, skip_obstacles);

		game_control().actual_targeting_type_ = target_type;
		game_control().wait_for_action([this](std::uint32_t used_on_index)
												  {
													  return use(used_on_index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
protected:
	std::int32_t range{Range};
	const target_types target_type{TargetType};
	const bool skip_obstacles{SkipObstacles};
};

template <std::int32_t Range,
		target_types TargetType = target_types::enemy,
		bool SkipObstacles = false>
class diagonal_target_ability : public active_ability {
public:
	void prepare(std::uint32_t index) override {
		game_control().selected_index_ = index;

		board_helper::calc_diagonal(index, game_control().possible_movements_,
									game_control().possible_movements_costs_,
									range, skip_obstacles);

		game_control().actual_targeting_type_ = target_type;
		game_control().wait_for_action([this](std::uint32_t used_on_index)
												  {
													  return use(used_on_index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
protected:
	std::int32_t range{Range};
	const target_types target_type{TargetType};
	const bool skip_obstacles{SkipObstacles};
};

template <std::int32_t Range,
		target_types TargetType = target_types::enemy,
		bool SkipObstacles = false>
class directed_target_ability : public active_ability {
public:
	void prepare(std::uint32_t index) override {
		game_control().selected_index_ = index;

		board_helper::calc_directed(index, game_control().possible_movements_,
									game_control().possible_movements_costs_,
									range, skip_obstacles);

		game_control().actual_targeting_type_ = target_type;
		game_control().wait_for_action([this](std::uint32_t used_on_index)
												  {
													  return use(used_on_index);
												  });
	}
	virtual void use(std::uint32_t use_on_index) = 0;
protected:
	std::int32_t range{Range};
	const target_types target_type{TargetType};
	const bool skip_obstacles{SkipObstacles};
};

#endif //PIGEONWAR_STRAIGHT_TARGET_TYPE_ABILITY_H
