#include <core/states_controller.h>
#include <core/board.h>
#include "long_range_missile.h"
#include "damage_dealers.h"

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
	animations_queue::push_animation(animation_types::move,
									 from_index,
									 to_index,
									 -1,
									 bitmap_key::long_range_missile);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 to_index,
									 150,
									 0,
									 bitmap_key::bum);
}