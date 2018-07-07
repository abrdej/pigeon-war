#include <messages/make_message.h>
#include "grenade.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "damage_dealers.h"
#include "sender.h"

void grenade::use(std::uint32_t index_on)
{
	if (used)
		return;

	used = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = game::get<board>().at(used_from_index);

	std::vector<std::uint32_t> neighbors;
	board_helper::neighboring_fields(index_on, neighbors, false);

	sender::send(make_action_message("grenade", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(ranged_damage(damage, game::get<board>().at(index_on), entity_id));

	for (auto& index : neighbors)
	{
		if (!game::get<board>().empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(damage / 2, game::get<board>().at(index), entity_id));
	}
}