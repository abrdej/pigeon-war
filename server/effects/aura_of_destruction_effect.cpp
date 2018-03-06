#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <components/modification.h>
#include "aura_of_destruction_effect.h"

bool aura_of_destruction_effect::set_effect(std::uint32_t entity_id) {

    auto aura_power = entity_manager::get(this->entity_id).get<power_filed>()->power;

    auto player_id = players_manager::player_for_entity(this->entity_id);

    if (aura_power > 0 &&
            player_id != players_manager::no_player &&
            players_manager::player_entity(player_id, entity_id) &&
            entity_manager::get(entity_id).contain<modification>()) {

        std::cout << "Apply aura\n";

        entity_manager::get(entity_id).get<modification>()->modify_damage_dealer_modifier_by(damage_increase);

        return true;
    }
    return false;
}

void aura_of_destruction_effect::remove_effect(std::uint32_t entity_id) {
    entity_manager::get(entity_id).get<modification>()->modify_damage_dealer_modifier_by(-damage_increase);
}