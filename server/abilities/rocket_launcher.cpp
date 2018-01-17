#include <sender.h>
#include <common/animations.h>
#include "rocket_launcher.h"
#include "damage_dealers.h"
#include "core/board.h"

void rocket_launcher::prepare(std::uint32_t index) {

	states::state_controller::selected_index_ = index;

	if (actual_rocket_type == rocket_types::long_range) {

		board_helper::calc_straight(index, states::state_controller::possible_movements_,
									states::state_controller::possible_movements_costs_,
									long_range_range, false);

		states::state_controller::actual_targeting_type_ = states::target_types::enemy;
		states::state_controller::wait_for_action([this](std::uint32_t used_on_index)
												  {
													  return use(used_on_index);
												  });

	} else if (actual_rocket_type == rocket_types::explosive) {

		path_finder path_finder(true);
		path_finder.calc(index);
		path_finder.get_possible_movements(states::state_controller::possible_movements_,
										   states::state_controller::possible_movements_costs_,
										   explosive_range);

		states::state_controller::actual_targeting_type_ = states::target_types::enemy;;
		states::state_controller::wait_for_action([this](std::uint32_t idx)
												  {
													  return use(idx);
												  });
	}
}

void rocket_launcher::use(std::uint32_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto enemy_id = board::at(index_on);

	if (actual_rocket_type == rocket_types::long_range) {

		auto used_from_pos = board::to_pos(used_from_index);
		auto used_to_pos = board::to_pos(index_on);

		auto distance = std::max(std::abs(static_cast<std::int32_t>(used_from_pos.first) - static_cast<std::int32_t>(used_to_pos.first)),
								 std::abs(static_cast<std::int32_t>(used_from_pos.second) - static_cast<std::int32_t>(used_to_pos.second)));

		std::int32_t final_damage = static_cast<std::int32_t>(base_damage + distance * distance_bonus + (has_rocket_change_bonus ? rocket_change_bonus : 0));

		sender::send(message_types::animation, animation_def::rocket_launcher, used_from_index, index_on);

		damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

	} else {

		std::int32_t real_damage = base_damage + (has_rocket_change_bonus ? rocket_change_bonus : 0);

		std::vector<std::uint32_t> neighbors;
		board_helper::neighboring_fields(index_on, neighbors, false);

		sender::send(message_types::animation, animation_def::flame_thrower, used_from_index, index_on);

		damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index_on), entity_id));

		for (auto& index : neighbors)
		{
			if (!board::empty(index))
				damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index), entity_id));
		}
	}

	used = true;
	has_rocket_change_bonus = false;
}