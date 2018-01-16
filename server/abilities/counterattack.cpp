#include "counterattack.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <core/board.h>
#include <components/damage_taker.h>
#include "sender.h"
#include "common/animations.h"

counterattack::counterattack(std::uint64_t entity_id)
		: entity_id(entity_id) {

	on_receive_damage(entity_id, [this](const damage_pack& dmg) {

		auto enemy_index = board::index_for(dmg.damage_dealer_id);

		std::vector<std::uint64_t> neighbors;
		board_helper::neighboring_fields(board::index_for(this->entity_id),
										 neighbors,
										 false);

		for (auto&& index : neighbors) {
			std::cout << index << "\n";
			if (index == enemy_index) {
				use(enemy_index);
				break;
			}
		}
	}, damage_taker::on_receive_damage_policy::after);
}

std::string counterattack::hint() const {
	std::string desc;
	desc = "Counterattack - native performs a counterattack if\n"
				   " the attacker is within his range.\n"
			"Counterattack deals " + std::to_string(damage) + " damage. It works only once per turn.";

	return std::move(desc);
}

void counterattack::use(std::uint64_t index_on) {

	if (used) {
		return;
	}

	auto entity_index = board::index_for(entity_id);
	auto enemy_id = board::at(index_on);

	sender::send(message_types::animation, animation_def::counterattack, entity_index, index_on);

	damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

	used = true;
}
