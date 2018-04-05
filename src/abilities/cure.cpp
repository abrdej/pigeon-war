#include "cure.h"

#include <core/board.h>
#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include <sender.h>
#include <components/power_field.h>
#include <components/applied_effects.h>
#include <messages/make_message.h>

#include "power_cost_ability.h"
#include "damage_dealers.h"

cure::cure(std::uint32_t entity_id)
        : entity_id(entity_id) {}


void cure::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	if (!use_ability_at_the_expense_of_power(entity_id, power_cost)) {
		return;
	}

	auto friend_id = board::at(index_on);

	sender::send(make_action_message("cure", index_on));

	standard_healing(healing_to_base_health(healing_amount_per_turn, friend_id));

    auto healing_amount_per_turn = this->healing_amount_per_turn;
    auto healing_duration = this->healing_duration;

	auto cure_connection = make_every_two_turns_from_next_callback_holder(healing_duration,
																		  [healing_amount_per_turn, friend_id]() {
																			  if (entity_manager::alive(friend_id)) {
																				  sender::send(
                                                                                          make_action_message("cure",
                                                                                                              board::index_for(
                                                                                                                      friend_id)));
																				  standard_healing(healing_to_base_health(healing_amount_per_turn, friend_id));
																			  }
																		  });

	auto cure_effect = make_positive_effect("cure");
	cure_effect->set_turn_connection(std::move(cure_connection));

	add_effect(friend_id, cure_effect);

	used = true;
}