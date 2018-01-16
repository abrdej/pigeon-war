#include "bomb.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <unordered_map>
#include <core/animations_queue.h>
#include "sender.h"
#include "common/animations.h"

bomb_detonation::bomb_detonation(std::uint64_t bomb_id) : bomb_id(bomb_id) {
//	onEveryRound([this]() {
//
//		if (waited) {
//			auto index = board::index_for(this->bomb_id);
//			use(index);
//		}
//
//		waited = true;
//	});
}

void bomb_detonation::look_for_bombs() {

}

void bomb_detonation::prepare(std::uint64_t for_index) {
//	states::state_controller::actual_state_ = states::states_types::wait_for_action;
//	states::state_controller::possible_movements_.push_back(for_index);
//	states::state_controller::actual_targeting_type_ = states::target_types::caster;
//	states::state_controller::wait_for_action([this](std::uint64_t index)
//											  {
//												  return use(index);
//											  });
}

void bomb_detonation::use(std::uint64_t for_index) {

	std::vector<std::uint64_t> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

	animations_queue::push_animation(animation_types::flash_bitmap, for_index, 150, 0, bitmap_key::bum);

	auto final_damage = damage;

	for (auto& index : neightbords)
	{
		auto id = board::at(index);
		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
			return *ptr == id;
		});
		if (it != buffer->end()) {
			final_damage += 5;
		}
	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}
	}

	entity_manager::destroy(bomb_id);
}

void bomb_detonation(std::uint64_t bomb_id, std::int32_t damage) {

	auto index = board::index_for(bomb_id);

	std::vector<std::uint64_t> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

	animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::bum);

//	auto final_damage = damage;
//
//	for (auto& index : neightbords)
//	{
//		auto id = board::at(index);
//		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
//			return *ptr == id;
//		});
//		if (it != buffer->end()) {
//			final_damage += 5;
//		}
//	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}

	}

	entity_manager::destroy(bomb_id);
}

bomb::bomb() {

}

void bomb::prepare(std::uint64_t for_index) {

}

void bomb::use(std::uint64_t index) {


}