#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <effects/auras_observer.h>
#include <effects/aura_of_destruction_effect.h>
#include <components/damage_taker.h>
#include <components/additions.h>
#include <sender.h>
#include <common/animations.h>
#include "aura_of_destruction.h"
#include "damage_dealers.h"

aura_of_destruction::aura_of_destruction(std::uint32_t entity_id)
        : entity_id(entity_id) {

    on_receive_damage(entity_id, [this, entity_id](const damage_pack& dmg) mutable {

        auto& aura_power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;

        auto half_damage = 0.5 * dmg.damage_value;

        auto value_for_power = std::min<std::int32_t>(aura_power, half_damage);
        aura_power -= value_for_power;

        if (value_for_power > 0) {
            sender::send(message_types::animation, animation_def::destruction, board::index_for(entity_id));

            auto enemy_id = dmg.damage_dealer_id;
            if (enemy_id != no_damage_dealer) {
                damage_dealers::standard_damage_dealer(magic_damage(value_for_power, enemy_id, entity_id));
            }
        }

    }, damage_taker::on_receive_damage_policy::after);
}

void aura_of_destruction::use(std::uint32_t use_on_index) {

//    auto& aura_power = entity_manager::get(entity_id).get<power_filed_with_charging>()->power;
//
//    if (aura_power < cost)
//        return;
//
//    aura_power -= cost;
//
//    std::vector<std::uint32_t> neighbors;
//    board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);
//    for (auto& index : neighbors) {
//        if (!board::empty(index) && players_funcs::player_entity(index)) {
//
//            auto friend_id = board::at(index);
//
//            auto usable_dmg_increase = this->usable_damage_increase;
//
//            entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(usable_dmg_increase);
//
//            auto destruction_receiver = make_after_n_turns_callback_holder(duration,
//                                                                           [usable_dmg_increase, friend_id]() mutable {
//
//
//                                                                               entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(-usable_dmg_increase);
//                                                                               remove_component(friend_id, "destruction_effect");
//                                                                           });
//
//            add_component(friend_id, "destruction_effect", destruction_receiver);
//        }
//    }
//
//    sender::send(message_types::animation, animation_def::destruction, board::index_for(entity_id));
//
//    auras_observer::observe();
}

std::string aura_of_destruction::hint() const {
    return "";
}