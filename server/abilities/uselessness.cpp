#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <sender.h>
#include <components/modification.h>
#include <components/additions.h>
#include "uselessness.h"
#include "common/animations.h"

uselessness::uselessness(std::uint32_t entity_id) : entity_id(entity_id) {

}

uselessness::~uselessness() {
    if (entity_id_with_uselessness != no_entity_with_uselessness && entity_manager::alive(entity_id_with_uselessness)) {
        remove_component(entity_id_with_uselessness,
                         "uselessness_effect");
    }
}

std::string uselessness::hint() const {
    auto power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;
    return "Magic power: " + std::to_string(power);
}

void uselessness::use(std::uint32_t index_on) {

    if (used)
        return;

    auto& power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;

    auto used_from_index = states::state_controller::selected_index_;
    auto enemy_id = board::at(index_on);

    entity_id_with_uselessness = enemy_id;

    auto reduction = damage_reduction_for_power * power;
    auto dmg_reduction_for_power = damage_reduction_for_power;

    entity_manager::get(enemy_id).get<modification>()->modify_damage_dealer_modifier_by(-reduction);

    auto uselessness_receiver = make_every_two_turns_from_next_callback_holder(power,
                                                                               [enemy_id, dmg_reduction_for_power](const turn_callback_info& info) mutable {

                                                                                   entity_manager::get(enemy_id).get<modification>()->modify_damage_dealer_modifier_by(dmg_reduction_for_power);

                                                                                   std::cout << entity_manager::get(enemy_id).get<modification>()->damage_dealer_modifier_value() << "\n";

                                                                                   if (info.ended && entity_manager::alive(enemy_id)) {
                                                                                       remove_component(enemy_id,
                                                                                                        "uselessness_effect");
                                                                                   }
                                                                               });

    add_component(enemy_id,
                  "uselessness_effect",
                  std::move(uselessness_receiver));

    sender::send(message_types::animation, animation_def::uselessness, index_on);

    power = 0;

    used = true;
}
