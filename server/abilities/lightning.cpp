#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <sender.h>
#include <common/animations.h>
#include <components/damage_pack.h>
#include <components/additions.h>
#include "lightning.h"
#include "damage_dealers.h"

lightning::lightning(std::uint32_t entity_id)
        : entity_id(entity_id) {}

std::string lightning::hint() const {
    auto power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;
    return "Magic power: " + std::to_string(power);
}

void lightning::use(std::uint32_t index_on) {

    if (used)
        return;

    auto& power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;

    if (power < power_cost)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);
    auto enemy_id = board::at(index_on);
    auto damage = this->damage;

    sender::send(message_types::animation, animation_def::lightning_prepare, index_on);

    auto lightning_holder = make_after_n_round_callback_holder(1,
                                                               [enemy_id, caster_id, damage]() mutable {
                                                                   auto caster_alive = entity_manager::alive(enemy_id);
                                                                   if (caster_alive) {
                                                                       sender::send(message_types::animation, animation_def::lightning, board::index_for(enemy_id));
                                                                       damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, caster_alive ? caster_id : no_damage_dealer));
                                                                       remove_component(enemy_id, "lightning_effect");
                                                                   }
                                                               });

    add_component(enemy_id,
                  "lightning_effect",
                  lightning_holder);

    power -= power_cost;

    used = true;
}