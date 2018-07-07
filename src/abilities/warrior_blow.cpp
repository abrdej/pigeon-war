#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include "warrior_blow.h"
#include "damage_dealers.h"
#include "sender.h"

void warrior_blow::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;


    sender::send(make_action_message("warrior_blow", used_from_index, index_on));

    auto enemy_id = game::get<board>().at(index_on);

    auto caster_id = game::get<board>().at(used_from_index);
    auto health_pack_ptr = game::get<entity_manager>().get(caster_id).get<health_field>();

    auto missing_health = health_pack_ptr->base_health - health_pack_ptr->health;

    auto damage_increase_factor = missing_health / 5;

    auto final_damage = damage_increase_factor * damage_per_factor + damage;

    damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

    used = true;
}