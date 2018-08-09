#include <components/applied_effects.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include "killer_instinct.h"
#include "abilities.h"
#include "server/sender.h"


killer_instinct::killer_instinct(std::uint32_t entity_id)
		: entity_id(entity_id) {
}

void killer_instinct::prepare(std::uint32_t for_index) {

	auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();

	auto moveable_ptr = abilities_ptr->get<moveable>();

	if (!moveable_ptr->has_range()) {
		game_control().possible_movements_.clear();
		return;
	}

	path_target_ability::prepare(for_index);

	auto possible_movements = std::move(game_control().possible_movements_);

	for (auto&& index : possible_movements) {
		if (game_board().empty(index)) {
			game_control().possible_movements_.push_back(index);
		}
	}
}

void killer_instinct::use(std::uint32_t index) {

//	if (used)
//		return;
//
//	sender::send(make_action_message("set_killer_instinct, entity_id);
//
//	auto killer_instinct_receiver = make_every_turn_callback_holder(1, [this]() mutable {
//
//		remove_effect(entity_id, "killer_instinct");
//
//		sender::send(make_action_message("remove_killer_instinct, entity_id);
//	});
//
//	add_effect(entity_id, "killer_instinct", std::move(killer_instinct_receiver));
//
//	auto move_from_index = game_control().selected_index_;
//
//	auto entity_id = game_board().take(move_from_index);
//
//	game_control().selected_index_ = states::no_selected_index;
//
//	sender::send(make_action_message("move, move_from_index, index);
//
//	game_board().give_back(entity_id, index);
//
//	game_control().selected_index_ = index;
//	game_control().possible_movements_.clear();
//
//	used = true;
//
//	auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
//
//	auto moveable_ptr = std::static_pointer_cast<moveable>(abilities_ptr->type(abilities::ability_types::moving));
//	moveable_ptr->remove_range();
}