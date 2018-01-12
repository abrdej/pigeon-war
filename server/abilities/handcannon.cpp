#include <core/states_controller.h>
#include "managers/abilities_manager.h"
#include "handcannon.h"
#include "damage_dealers.h"
#include "abilities.h"
#include "protection_field.h"

void handcannon::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    auto& caster_abilities = abilities_manager::component_for(caster_id);
    auto protection_field_ptr = std::static_pointer_cast<protection_field>(caster_abilities.type(abilities::ability_types::special));
    auto is_active = protection_field_ptr->active();

    auto final_damage = is_active ? bonus_damage + damage : damage;

    std::cout << "active: " << is_active << " final_damage: " << final_damage << "\n";

    sender::send(message_types::animation, animation_def::handcannon, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(final_damage, board::at(index_on), caster_id));

    used = true;
}