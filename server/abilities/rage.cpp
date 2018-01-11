#include <managers/health_manager.h>
#include <core/states_controller.h>
#include "rage.h"
#include "damage_dealers.h"
#include <iostream>

rage::rage(size_t id) : entity_id(id) {
	onEveryRound([this]() {
		damage_this_turn = 0;
	});

	healths_manager::on_receive_damage(entity_id, [this](const damage_pack&) {

		std::cout << "on receive damage\n";

		++damage_this_turn;
		if (damage_this_turn == required_damage) {
			std::cout << "used\n";
			use();
		}
	}, healths_manager::on_receive_damage_policy::after);
}

void rage::use() {

	auto use_from_index = board::index_for(entity_id);

	std::vector<size_t> around_fields_ids;
	board_helper::neighboring_fields(use_from_index, around_fields_ids, false);

	sender::send(message_types::animation, animation_def::rage, use_from_index);

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id)) {
			damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
		}
	}
}