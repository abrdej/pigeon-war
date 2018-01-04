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

	//audio::shoot_sound();

	auto use_from_index = board::index_for(entity_id);

	std::vector<size_t> around_fields_ids;
	board_helper::neighboring_fields(use_from_index, around_fields_ids, false);

	play_animation(use_from_index);

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id)) {
			damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
		}
	}
}

void rage::play_animation(size_t use_from_index) {

	auto entity_id = board::take(use_from_index);

	auto from_cr = board::to_pos(use_from_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(from_cr.first, from_cr.second),
									 150,
									 0,
									 bitmap_key::troll_rage);

	board::give_back(entity_id, use_from_index);
}