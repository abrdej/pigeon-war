#include <managers/health_manager.h>
#include <core/states.h>
#include "rage.h"
#include "damage_dealers.h"
#include "managers/types_manager.h"
#include <iostream>
#include <animation/animation.h>

rage::rage(size_t id) : entity_id(id) {
	onEveryTurn([this]() {
		damage_this_turn = 0;
	});

	healths_manager::on_receive_damage(entity_id, [this]() {

		std::cout << "on receive damage\n";

		++damage_this_turn;
		if (damage_this_turn == required_damage) {
			std::cout << "used\n";
			use();
		}
	});
}

void rage::use() {

	//audio::shoot_sound();

	auto use_from_index = board::index_for(entity_id);

	std::vector<size_t> around_fields_ids;
	board_helper::neighboring_fields(use_from_index, around_fields_ids, false);

	play_animation(use_from_index);

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id)) {
			damage_dealers::standard_damage_dealer(damage_, board::at(field_id));
		}
	}
}

void rage::play_animation(size_t use_from_index) {

	auto entity_id = board::take(use_from_index);
	auto type = types_manager::component_for(entity_id);

	auto from_cr = board::to_pos(use_from_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(
			animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
									std::chrono::milliseconds(150),
									"troll_rage.png"));
	animation::base_player::play();
	board::give_back(entity_id, use_from_index);
}