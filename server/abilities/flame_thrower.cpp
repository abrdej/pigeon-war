#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/states_controller.h>

void flame_thrower::use(sf::Uint64 index_on) {

	if (used)
		return;

	sf::Int32 real_damage = damage;

	if (counter == 2) {
		real_damage += damage_bonus;
		counter = 0;
	}

	used = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<sf::Uint64> neightbords;
	board_helper::neighboring_fields(index_on, neightbords, false);

	sender::send(message_types::animation, animation_def::flame_thrower, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index_on), entity_id));

	for (auto& index : neightbords)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(real_damage, board::at(index), entity_id));
	}

	++counter;
}