#include <core/states_controller.h>
#include <core/board.h>
#include <components/applied_effects.h>
#include <managers/entity_manager.h>
#include <effects/hypnosis_effect.h>
#include <common/make_message.h>
#include "hypnosis.h"
#include "abilities.h"
#include "core/turn_system.h"
#include "sender.h"
#include "common/animations.h"

void hypnosis::use(std::uint32_t index_on) {

	if (used)
		return;

	sender::send(make_animation_message("hypnosis", index_on));

	auto enemy_id = board::at(index_on);

    auto enemy_abilities_ptr = entity_manager::get(enemy_id).get<abilities>();
	enemy_abilities_ptr->is_active = false;

    auto hypnosis_connection = make_after_n_round_callback_holder(duration,
																[enemy_id]() mutable {

																	auto inner_enemy_abilities_ptr = entity_manager::get(enemy_id).get<abilities>();
																	inner_enemy_abilities_ptr->is_active = true;

																	remove_effect(enemy_id,
																				  "hypnotised");
																});

    auto hypnosis_effect = make_negative_effect("hypnotised");
    hypnosis_effect->set_turn_connection(std::move(hypnosis_connection));

	add_effect(enemy_id, hypnosis_effect);

	used = true;
}