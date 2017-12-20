#include "counterattack.h"
#include "damage_dealers.h"
#include <managers/health_manager.h>
#include <core/states_controller.h>
#include <core/board.h>
#include <client/animation/animation.h>

counterattack::counterattack(std::size_t entity_id)
		: entity_id(entity_id) {

	onEveryRound([this](){
		used = false;
	});

	healths_manager::on_receive_damage(entity_id, [this](const damage_pack& dmg) {

		auto enemy_index = board::index_for(dmg.damage_dealer_id);

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

	damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

	used = true;
}

void counterattack::play_animation(size_t from_index, size_t to_index) {

	auto entity_id = board::take(from_index);

	animations_queue::push_animation(animation_types::move, from_index, to_index, entity_id, bitmap_key::none);
	animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, bitmap_key::native_attack);
	animations_queue::push_animation(animation_types::move, to_index, from_index, entity_id, bitmap_key::none);

	board::give_back(entity_id, from_index);
}
