#include "aura_of_immunity_effect.h"
#include <components/additions.h>
#include <components/modification.h>
#include <sender.h>
#include <common/animations.h>

void aura_of_immunity_effect::set_effect(std::uint32_t entity_id) {
	if (entity_manager::get(entity_id).contain<modification>()) {
		entity_manager::get(entity_id).get<modification>()->modify_damage_dealer_modifier_by(-damage_reduction);
		sender::send(message_types::animation, animation_def::aura_of_immunity, board::index_for(entity_id));
	}
}

void aura_of_immunity_effect::remove_effect(std::uint32_t entity_id) {
	entity_manager::get(entity_id).get<modification>()->modify_damage_dealer_modifier_by(damage_reduction);
	sender::send(message_types::animation, animation_def::aura_of_immunity_break, board::index_for(entity_id));
}