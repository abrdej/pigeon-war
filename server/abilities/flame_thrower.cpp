#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/states_controller.h>

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