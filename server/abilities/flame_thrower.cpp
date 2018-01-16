#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/states_controller.h>
#include "sender.h"
#include "common/animations.h"

void flame_thrower::use(std::uint64_t index_on) {

	if (used)
		return;

	std::int32_t real_damage = damage;

	if (counter == 2) {
		real_damage += damage_bonus;
		counter = 0;
	}

	used = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<std::uint64_t> neightbords;
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