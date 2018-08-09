#include <messages/make_message.h>
#include "basic_melee_attack.h"
#include "core/path_finder.h"
#include "core/game_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "server/sender.h"

void basic_melee_attack::use(std::uint32_t index_on)
{
	if (used) {
		return;
	}

	auto used_from_index = game_control().selected_index_;
	auto caster_id = game_board().at(used_from_index);

	sender::send(make_action_message("basic_melee_attack", used_from_index, index_on));

	auto enemy_id = game_board().at(index_on);

	damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

	used = true;
}