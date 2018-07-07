#include "aura_of_immunity_effect.h"
#include <components/applied_effects.h>
#include <components/modification.h>
#include <sender.h>
#include <managers/players_manager.h>

bool aura_of_immunity_effect::set_effect(std::uint32_t entity_id) {

	auto player_id = game::get<players_manager>().player_for_entity(this->entity_id);


	if (player_id != game::get<players_manager>().no_player &&
			game::get<players_manager>().player_entity(player_id, entity_id) &&
            game::get<entity_manager>().get(entity_id).contain<modification>()) {

		std::cout << "Apply aura\n";

		game::get<entity_manager>().get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction);

		return true;
	}
	return false;
}

void aura_of_immunity_effect::remove_effect(std::uint32_t entity_id) {
	if (game::get<entity_manager>().get(entity_id).contain<modification>()) {

		std::cout << "Remove aura\n";

		game::get<entity_manager>().get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(damage_reduction);
	}
}