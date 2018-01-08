#include "tongue_of_fire.h"

#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

void tongue_of_fire::use(size_t index_on)
{
	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	play_bullet_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	// show damage animation // for example. -9 dmg

	used = true;
}

void tongue_of_fire::play_bullet_animation(size_t from_index, size_t to_index)
{
	animations_queue::push_animation(animation_types::move,
									 from_index,
									 to_index,
									 -1,
									 bitmap_key::tongue_of_fire);
}