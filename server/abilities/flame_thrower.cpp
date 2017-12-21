#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/states_controller.h>

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
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void flame_thrower::use(size_t index_on) {

	if (used)
		return;

	int real_damage = damage;

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

	damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index_on), entity_id));

	for (auto& index : neightbords)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index), entity_id));
	}

	++counter;
}

void flame_thrower::play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords) {

	animations_queue::push_animation(animation_types::move, from_index, to_index, -1, bitmap_key::flame_thrower);
	animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, bitmap_key::shards);

	for (auto& index : neightbords)
		animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::tongue_of_fire);
}