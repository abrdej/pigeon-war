#include <core/states_controller.h>
#include <core/board.h>
#include <components/additions.h>
#include <managers/entity_manager.h>
#include "hypnosis.h"
#include "core/turn_system.h"
#include "sender.h"
#include "common/animations.h"

void hypnosis::use(std::uint32_t index_on) {

	if (used)
		return;

	sender::send(message_types::animation, animation_def::hypnosis, index_on);

	auto enemy_id = board::at(index_on);

	auto enemy_abilities_ptr = entity_manager::get(enemy_id).get<abilities>();
	enemy_abilities_ptr->is_active = false;

	auto hypnosis_receiver = make_after_n_round_callback_holder(duration,
																[enemy_id]() mutable {

																	auto inner_enemy_abilities_ptr = entity_manager::get(enemy_id).get<abilities>();
																	inner_enemy_abilities_ptr->is_active = true;

																	remove_component(enemy_id,
																					 "hypnosis");
																});

	add_component(enemy_id, "hypnosis", hypnosis_receiver);

	used = true;
}

std::string hypnosis::hint() const {

	std::string desc;

	desc = "Hypnosis - causes that the enemy unit will not be able to make a move\n"
			" in the next turn.\n"
			"It can be used only once per battle.";
	return std::move(desc);
}