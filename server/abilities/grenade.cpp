#include "grenade.h"

#include "core/states_controller.h"
#include "core/path_finder.h"
#include "damage_dealers.h"
#include <chrono>

std::string grenade::hint() const {

	std::string desc;

	desc = "Grenade - deals area damage of: " + std::to_string(damage) + " for main target\n"
			"and half of that around.\n"
			"It can be used only once per battle.";
	return std::move(desc);
}

void grenade::use(sf::Uint64 index_on)
{
	if (used_)
		return;

	used_ = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<sf::Uint64> neighbors;
	board_helper::neighboring_fields(index_on, neighbors, false);

	sender::send(message_types::animation, animation_def::grenade, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	for (auto& index : neighbors)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(damage / 2, board::at(index), entity_id));
	}
}