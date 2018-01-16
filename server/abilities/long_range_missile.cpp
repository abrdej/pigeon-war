#include <core/states_controller.h>
#include <core/board.h>
#include <core/animations_queue.h>
#include "long_range_missile.h"
#include "damage_dealers.h"

void long_range_missile::use(std::uint64_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	play_animation(used_from_index, index_on);

	auto enemy_id = board::at(index_on);

	auto used_from_pos = board::to_pos(used_from_index);
	auto used_to_pos = board::to_pos(index_on);

	auto distance = std::max(std::abs(static_cast<std::int32_t>(used_from_pos.first) - static_cast<std::int32_t>(used_to_pos.first)),
							 std::abs(static_cast<std::int32_t>(used_from_pos.second) - static_cast<std::int32_t>(used_to_pos.second)));

	std::cout << "distance: " << distance << "\n";

	std::int32_t final_damage = static_cast<std::int32_t>(start_damage + distance * additional_damage);

	damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

	used = true;
}

void long_range_missile::play_animation(std::uint64_t from_index, std::uint64_t to_index) {
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