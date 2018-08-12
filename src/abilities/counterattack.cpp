#include "counterattack.h"
#include "damage_dealers.h"
#include <core/game_controller.h>
#include <core/board.h>
#include <components/damage_taker.h>
#include <messages/make_message.h>
#include "server/sender.h"

counterattack::counterattack(std::uint32_t entity_id)
		: entity_id(entity_id) {

	on_receive_damage(entity_id, [this](const damage_pack& dmg) {

		if (game::get<entity_manager>().get(this->entity_id).get<health_field>()->health > 0) {
			auto enemy_index = game_board().index_for(dmg.damage_dealer_id);

			std::vector<std::uint32_t> neighbors;
			board_helper::neighboring_fields(game_board().index_for(this->entity_id),
											 neighbors,
											 false);

			for (auto&& index : neighbors) {
				std::cout << index << "\n";
				if (index == enemy_index) {
					use(enemy_index);
					break;
				}
			}
		}
	}, damage_taker::on_receive_damage_policy::after);
}

void counterattack::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	auto enemy_id = game_board().at(index_on);

	sender::send(make_action_message("counterattack", enemy_id, index_on));

	damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

	used = true;
}
