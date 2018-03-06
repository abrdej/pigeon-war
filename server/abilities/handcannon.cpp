#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <common/make_message.h>
#include "handcannon.h"
#include "damage_dealers.h"
#include "abilities.h"
#include "protection_field.h"
#include "sender.h"
#include "common/animations.h"

void handcannon::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    auto abilities_ptr = entity_manager::get(caster_id).get<abilities>();
    auto protection_field_ptr = abilities_ptr->get<protection_field>();
    auto is_active = protection_field_ptr->active();

    auto final_damage = is_active ? bonus_damage + damage : damage;

    std::cout << "active: " << is_active << " final_damage: " << final_damage << "\n";

    sender::send(make_animation_message("handcannon", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(ranged_damage(final_damage, board::at(index_on), caster_id));

    used = true;
}