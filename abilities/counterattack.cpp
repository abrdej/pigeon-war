#include "counterattack.h"
#include "damage_dealers.h"
#include <managers/health_manager.h>
#include <core/states.h>
#include <core/board.h>
#include <animation/animation.h>
#include <managers/types_manager.h>

counterattack::counterattack(std::size_t entity_id)
		: entity_id(entity_id) {

	onEveryRound([this](){
		used = false;
	});

	healths_manager::on_receive_damage_with_attacker(entity_id, [this](size_t attacker_id) {

		auto enemy_index = board::index_for(attacker_id);

		std::vector<std::size_t> neighbors;
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
	}, healths_manager::on_receive_damage_policy::after);
}

void counterattack::use(size_t index_on) {

	if (used) {
		return;
	}

	auto entity_index = board::index_for(entity_id);
	auto enemy_id = board::at(index_on);

	play_animation(entity_index, index_on);

	damage_dealers::standard_damage_dealer(damage, enemy_id, entity_id);

	used = true;
}

void counterattack::play_animation(size_t from_index, size_t to_index) {

	auto entity_id = board::take(from_index);
	auto type = types_manager::component_for(entity_id);
	animation::player<animation::move>::launch(animation::move(from_index, to_index, type));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "native_attack.png"));
	animation::base_player::play();
	animation::player<animation::move>::launch(animation::move(to_index, from_index, type));
	animation::base_player::play();
	board::give_back(entity_id, from_index);
}
