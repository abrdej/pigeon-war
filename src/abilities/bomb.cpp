#include "bomb.h"
#include "damage_dealers.h"
#include <core/game_controller.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <entities/entities_factory.h>
#include "server/sender.h"

bomb_detonation::bomb_detonation(std::uint32_t bomb_id) : bomb_id(bomb_id) {
//	onEveryRound([this]() {
//
//		if (waited) {
//			auto index = game_board().index_for(this->bomb_id);
//			use(index);
//		}
//
//		waited = true;
//	});
}

void bomb_detonation::look_for_bombs() {

}

void bomb_detonation::prepare(std::uint32_t for_index) {
//	game_control().actual_state_ = states::states_types::wait_for_action;
//	game_control().possible_movements_.push_back(for_index);
//	game_control().actual_targeting_type_ = target_types::caster;
//	game_control().wait_for_action([this](std::uint32_t index)
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
		auto id = game_board().at(index);
		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
			return *ptr == id;
		});
		if (it != buffer->end()) {
			final_damage += 5;
		}
	}

	for (auto& index : neightbords)
	{
		if (!game_board().empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, game_board().at(index)));
		}
	}

	game::get<entity_manager>().destroy(bomb_id);
}

void bomb_detonation(std::uint32_t bomb_id, std::int32_t damage) {

	auto index = game_board().index_for(bomb_id);

	std::vector<std::uint32_t> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

//	animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, "bum);

//	auto final_damage = damage;
//
//	for (auto& index : neightbords)
//	{
//		auto id = game_board().at(index);
//		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
//			return *ptr == id;
//		});
//		if (it != buffer->end()) {
//			final_damage += 5;
//		}
//	}

	for (auto& index : neightbords)
	{
		if (!game_board().empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, game_board().at(index)));
		}

	}

	game::get<entity_manager>().destroy(bomb_id);
}

bomb::bomb(std::uint32_t entity_id) : path_target_ability(4, target_types::moving, true), entity_id(entity_id) {
	after_player_turn(entity_id, [this]() {
		++bombs;
	});
}

void bomb::use(std::uint32_t index) {
	if (bombs == 0)
		return;

	auto bomb_id = entities_factory::create("bomb_instance");

	game::get<players_manager>().add_entity_for_player(game::get<players_manager>().player_for_entity(entity_id), bomb_id);
	game_board().insert(index, bomb_id);

	sender::send(make_create_entity_message(bomb_id));

	--bombs;
}
