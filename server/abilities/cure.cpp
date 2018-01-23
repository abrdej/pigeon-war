#include <common/message_types.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include <common/animations.h>
#include <sender.h>
#include <components/power_field.h>
#include <components/additions.h>
#include "cure.h"

cure::cure(std::uint32_t entity_id)
        : entity_id(entity_id) {}


void cure::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	auto& power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;

	if (power < power_cost)
		return;

	auto friend_id = board::at(index_on);

	sender::send(message_types::animation, animation_def::cure, index_on);

    entity_manager::get(friend_id).get<damage_taker>()->heal(healing(healing_amount_per_turn,
                                                                     friend_id));

    auto healing_amount_per_turn = this->healing_amount_per_turn;
    auto healing_duration = this->healing_duration;

    auto healing_holder = make_every_two_turns_from_next_callback_holder(healing_duration,
                                                                         [healing_amount_per_turn, friend_id]() {
																			 if (entity_manager::alive(friend_id)) {
																				 sender::send(message_types::animation, animation_def::cure, board::index_for(friend_id));
																				 entity_manager::get(friend_id).get<damage_taker>()->heal(healing(healing_amount_per_turn,
																																				  friend_id));
																			 }
                                                                         });

//    entity_manager::get(friend_id).get<addition>()->named_data.clear();

    add_component(friend_id, "cure_effect", healing_holder);

	power -= power_cost;

	used = true;
}