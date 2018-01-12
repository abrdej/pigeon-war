#include "tongue_of_fire.h"

#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

void tongue_of_fire::use(sf::Uint64 index_on)
{
	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	sender::send(message_types::animation, animation_def::tongue_of_fire, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	// show damage animation // for example. -9 dmg

	used = true;
}