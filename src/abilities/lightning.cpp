#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <sender.h>
#include <components/damage_pack.h>
#include <components/applied_effects.h>
#include <messages/make_message.h>
#include "lightning.h"
#include "damage_dealers.h"
#include "power_cost_ability.h"

lightning::lightning(std::uint32_t entity_id)
        : entity_id(entity_id) {}

std::string lightning::hint() const {

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    auto desc = get_desc("lightning");
    str_replace(desc, "<power>", std::to_string(power));
    str_replace(desc, "<damage>", std::to_string(damage));
    str_replace(desc, "<power_cost>", std::to_string(power_cost));

    return desc;
}

void lightning::use(std::uint32_t index_on) {

    if (used)
        return;

    if (!use_ability_at_the_expense_of_power(entity_id, power_cost)) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = game::get<board>().at(used_from_index);
    auto enemy_id = game::get<board>().at(index_on);
    auto damage = this->damage;

    sender::send(make_action_message("lightning_prepare", index_on));

    auto lightning_connection = make_after_n_round_callback_holder(1,
                                                               [enemy_id, caster_id, damage]() mutable {
                                                                   if (game::get<entity_manager>().alive(enemy_id)) {
                                                                       sender::send(make_action_message("lightning",
                                                                                                        game::get<board>().index_for(
                                                                                                                enemy_id)));
                                                                       damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, game::get<entity_manager>().alive(caster_id) ? caster_id : no_damage_dealer));
                                                                       remove_effect(enemy_id, "lightning target");
                                                                   }
                                                               });

    auto lightning_target = make_not_removable_negative_effect("lightning target");
    lightning_target->set_turn_connection(std::move(lightning_connection));

    add_effect(enemy_id, lightning_target);

    used = true;
}