#include "bomb.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <entities/entities_factory.h>
#include "sender.h"

bomb_detonation::bomb_detonation(std::uint32_t bomb_id) : bomb_id(bomb_id) {
//	onEveryRound([this]() {
//
//		if (waited) {
//			auto index = game::get<board>().index_for(this->bomb_id);
//			use(index);
//		}
//
//		waited = true;
//	});
}

void bomb_detonation::look_for_bombs() {

}

void bomb_detonation::prepare(std::uint32_t for_index) {
//	states::state_controller::actual_state_ = states::states_types::wait_for_action;
//	states::state_controller::possible_movements_.push_back(for_index);
//	states::state_controller::actual_targeting_type_ = target_types::caster;
//	states::state_controller::wait_for_action([this](std::uint32_t index)
//											  {
//												  return use(index);
//											  });
}

void bomb_detonation::use(std::uint32_t for_index) {

	std::vector<std::uint32_t> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

//	animations_queue::push_animation(animation_types::flash_bitmap, for_index, 150, 0, "bum);

	auto final_damage = damage;

	for (auto& index : neightbords)
	{
		auto id = game::get<board>().at(index);
		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
			return *ptr == id;
		});
		if (it != buffer->end()) {
			final_damage += 5;
		}
	}

	for (auto& index : neightbords)
	{
		if (!game::get<board>().empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, game::get<board>().at(index)));
		}
	}

	game::get<entity_manager>().destroy(bomb_id);
}

void bomb_detonation(std::uint32_t bomb_id, std::int32_t damage) {

	auto index = game::get<board>().index_for(bomb_id);

	std::vector<std::uint32_t> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

//	animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, "bum);

//	auto final_damage = damage;
//
//	for (auto& index : neightbords)
//	{
//		auto id = game::get<board>().at(index);
//		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
//			return *ptr == id;
//		});
//		if (it != buffer->end()) {
//			final_damage += 5;
//		}
//	}

	for (auto& index : neightbords)
	{
		if (!game::get<board>().empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, game::get<board>().at(index)));
		}

	}

	game::get<entity_manager>().destroy(bomb_id);
}

bomb::bomb(std::uint32_t entity_id) : entity_id(entity_id) {
	after_player_turn(entity_id, [this]() {
		++bombs;
	});
}

void bomb::use(std::uint32_t index) {
	if (bombs == 0)
		return;

	auto bomb_id = entities_factory::create("bomb_instance");

	game::get<players_manager>().add_entity_for_player(game::get<players_manager>().player_for_entity(entity_id), bomb_id);
	game::get<board>().insert(index, bomb_id);

    auto health = game::get<entity_manager>().get(bomb_id).get<health_field>()->health;
    auto name = game::get<entity_manager>().get(bomb_id).name;

	sender::send(make_create_entity_message(bomb_id, name, health, index));

	--bombs;
}