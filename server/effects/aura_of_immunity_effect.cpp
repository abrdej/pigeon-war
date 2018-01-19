#include "aura_of_immunity_effect.h"
#include <components/additions.h>
#include <components/modification.h>
#include <sender.h>
#include <common/animations.h>

void aura_of_immunity_effect::set_effect(std::uint32_t entity_id) {
	if (entity_manager::get(entity_id).contain<modification>()) {

		std::cout << "Apply aura\n";

		entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction);
	}
}

void aura_of_immunity_effect::remove_effect(std::uint32_t entity_id) {
	if (entity_manager::get(entity_id).contain<modification>()) {

		std::cout << "Remove aura\n";

		entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(damage_reduction);
	}
}