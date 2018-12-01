#include <abilities/warrior_blow.h>

#include <abilities/damage_dealers.h>
#include <core/game_controller.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include <server/sender.h>

warrior_blow::warrior_blow(std::uint32_t entity_id) : entity_id(entity_id) {}

void warrior_blow::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    sender::send(make_action_message("warrior_blow", entity_id, index_on));

    auto health_pack_ptr = game::get<entity_manager>().get(entity_id).get<health_field>();

    auto missing_health = health_pack_ptr->base_health - health_pack_ptr->health;

    auto damage_increase_factor = missing_health / 5;

    auto final_damage = damage_increase_factor * damage_per_factor + damage;

    damage_dealers::standard_damage_dealer(melee_damage(final_damage, game_board().at(index_on), entity_id));

    used = true;
}
