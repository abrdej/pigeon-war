#include <core/states_controller.h>
#include "rage.h"
#include "damage_dealers.h"
#include <iostream>
#include <common/make_message.h>
#include "sender.h"
#include "common/animations.h"
#include "components/damage_taker.h"

rage::rage(std::uint32_t id) : entity_id(id) {
	on_every_two_turns_from_next([this]() {
		damage_this_turn = 0;
	});

	on_receive_damage(entity_id, [this](const damage_pack&) {

		++damage_this_turn;
		if (damage_this_turn == required_damage) {
			use();
			damage_this_turn = 0;
		}
	}, damage_taker::on_receive_damage_policy::after);
}

void rage::use() {

	auto use_from_index = board::index_for(entity_id);

	std::vector<std::uint32_t> around_fields_ids;
	board_helper::neighboring_fields(use_from_index, around_fields_ids, false);

	sender::send(make_action_message("rage", use_from_index));

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id)) {
			damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
		}
	}
}