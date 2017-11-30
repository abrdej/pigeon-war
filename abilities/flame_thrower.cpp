#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/states.h>
#include <animation/animation.h>

flame_thrower::flame_thrower() {
	onEveryRound([this]() {
		used = false;
	});
}

void flame_thrower::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range_);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void flame_thrower::use(size_t index_on) {

	if (used)
		return;

	int real_damage = damage_;

	if (counter == 2) {
		real_damage += damage_bonus;
		counter = 0;
	}

	used = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(index_on, neightbords, false);

	play_animation(used_from_index, index_on, neightbords);

	damage_dealers::standard_damage_dealer(real_damage, board::at(index_on), entity_id);

	for (auto& index : neightbords)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(real_damage, board::at(index), entity_id);
	}

	++counter;
}

void flame_thrower::play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords) {
	animation::player<animation::move>::launch(animation::move(from_index, to_index, typeid(*this)));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "shards.png"));
	for (auto& index : neightbords)
		animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "tongue_of_fire.png"));
	animation::base_player::play();
}