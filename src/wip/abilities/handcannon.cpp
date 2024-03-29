#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <handcannon.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/abilities.h>
#include <protection_field.h>
#include <turn_based/sender.h>
#include <turn_based/board.h>

void handcannon::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);

    auto abilities_ptr = game::get<entity_manager>().get(caster_id).get<abilities>();
    auto protection_field_ptr = abilities_ptr->get<protection_field>();
    auto is_active = protection_field_ptr->active();

    auto final_damage = is_active ? bonus_damage + damage : damage;

    LOG(debug) << "active: " << is_active << " final_damage: " << final_damage;

    sender::send(make_action_message("handcannon", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(ranged_damage(final_damage, game_board().at(index_on), caster_id));

    used = true;
}