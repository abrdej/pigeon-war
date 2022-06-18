#include <turn_based/game_controller.h>
#include <turn_based/board.h>
#include <components/applied_effects.h>
#include <turn_based/managers/entity_manager.h>
#include <effects/hypnosis_effect.h>
#include <messages/massages_makers.h>
#include <hypnosis.h>
#include <turn_based/abilities.h>
#include <turn_based/turn_system.h>
#include <turn_based/sender.h>

hypnosis::hypnosis() : path_target_ability(4, target_types::enemy, true) {}

void hypnosis::use(std::uint32_t index_on) {

	if (used)
		return;

	sender::send(make_action_message("hypnosis", index_on));

	auto enemy_id = game_board().at(index_on);

    auto enemy_abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();
	enemy_abilities_ptr->is_active = false;

    auto hypnosis_connection = make_after_n_round_callback_holder(duration,
																[enemy_id]() mutable {

																	auto inner_enemy_abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();
																	inner_enemy_abilities_ptr->is_active = true;

																	remove_effect(enemy_id,
																				  "hypnotised");
																});

    auto hypnosis_effect = make_negative_effect("hypnotised");
    hypnosis_effect->set_turn_connection(std::move(hypnosis_connection));

	add_effect(enemy_id, hypnosis_effect);

	used = true;
}