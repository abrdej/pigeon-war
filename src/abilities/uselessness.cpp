#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <server/sender.h>
#include <components/modification.h>
#include <components/applied_effects.h>
#include <messages/massages_makers.h>
#include "uselessness.h"

uselessness::uselessness(std::uint32_t entity_id)
  : path_target_ability(3), entity_id(entity_id) {

}

uselessness::~uselessness() {
    if (entity_id_with_uselessness != no_entity_with_uselessness && game::get<entity_manager>().alive(entity_id_with_uselessness)) {
        remove_effect(entity_id_with_uselessness,
                      "uselessness_effect");
    }
}

std::string uselessness::hint() const {
    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;
    return "Magic power: " + std::to_string(power);
}

void uselessness::use(std::uint32_t index_on) {

    if (used)
        return;

    auto& power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    auto used_from_index = game_control().selected_index_;
    auto enemy_id = game_board().at(index_on);

    entity_id_with_uselessness = enemy_id;

    auto reduction = damage_reduction_for_power * power;
    auto dmg_reduction_for_power = damage_reduction_for_power;

    game::get<entity_manager>().get(enemy_id).get<modification>()->modify_by(modifiers::damage_dealer, -reduction);

    auto uselessness_connection = make_every_two_turns_from_next_callback_holder(power,
                                                                               [enemy_id, dmg_reduction_for_power](const turn_callback_info& info) mutable {
                                                                                   game::get<entity_manager>().get(enemy_id).get<modification>()->modify_by(modifiers::damage_dealer, dmg_reduction_for_power);
                                                                                   if (info.is_ending) {
                                                                                       remove_effect(enemy_id,
                                                                                                     "uselessness");
                                                                                   }
                                                                               });

    auto uselessness_effect = make_negative_effect("uselessness");
    uselessness_effect->set_turn_connection(std::move(uselessness_connection));

    add_effect(enemy_id, uselessness_effect);

    sender::send(make_action_message("uselessness", index_on));

    power = 0;

    used = true;
}
