#include <core/states_controller.h>
#include <core/board.h>
#include "long_range_missile.h"
#include "damage_dealers.h"

long_range_missile::long_range_missile() {

}

void long_range_missile::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
								states::state_controller::possible_movements_costs_,
								range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void long_range_missile::use(size_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	play_animation(used_from_index, index_on);

	auto enemy_id = board::at(index_on);

	auto used_from_pos = board::to_pos(used_from_index);
	auto used_to_pos = board::to_pos(index_on);

	auto distance = std::max(std::abs(static_cast<int>(used_from_pos.first) - static_cast<int>(used_to_pos.first)),
							 std::abs(static_cast<int>(used_from_pos.second) - static_cast<int>(used_to_pos.second)));

	std::cout << "distance: " << distance << "\n";

	int final_damage = static_cast<int>(start_damage + distance * additional_damage);

	damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

	used = true;
}

void long_range_missile::play_animation(size_t from_index, size_t to_index) {
	animation::player<animation::move>::launch
			(animation::move(from_index, to_index, bitmap_key::long_range_missile));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch
			(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();
}