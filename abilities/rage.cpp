#include <managers/health_manager.h>
#include <core/states.h>
#include <animation/animation.h>
#include "rage.h"
#include "damage_dealers.h"

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

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id)) {
			damage_dealers::standard_damage_dealer(damage_, field_id);
		}
	}
}

void rage::play_animation(size_t for_index) {

	auto ii = board::to_col_row(for_index);

	animation::player<animation::flash_bitmap>::launch(
			animation::flash_bitmap(board::to_index(ii.first - 1, ii.second - 1),
									std::chrono::milliseconds(150),
									"troll_angry.png"));
	animation::base_player::play();

}