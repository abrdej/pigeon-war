#include "grenade.h"

#include "core/states_controller.h"
#include "core/path_finder.h"
#include "damage_dealers.h"
#include <chrono>

void grenade::use(size_t index_on)
{
	if (used_)
		return;

	used_ = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<size_t> neighbors;
	board_helper::neighboring_fields(index_on, neighbors, false);

	sender::send(message_types::animation, animation_def::grenade, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	for (auto& index : neighbors)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(damage / 2, board::at(index), entity_id));
	}
}

//void grenade::play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords)
//{
//
//	animations_queue::push_animation(animation_types::move, from_index, to_index, -1, bitmap_key::grenade);
//	animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, bitmap_key::bum);
//
//	for (auto& index : neightbords)
//		if (!board::empty(index))
//			animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::shards);
//}