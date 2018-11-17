#include "aura_of_destruction.h"

#include <components/damage_taker.h>
#include <components/power_field.h>
#include <abilities/damage_dealers.h>
#include <managers/entity_manager.h>

aura_of_destruction::aura_of_destruction(std::uint32_t entity_id)
        : entity_id(entity_id) {

    on_receive_damage(entity_id, [this, entity_id](const damage_pack& dmg) mutable {

        auto& aura_power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

        auto half_damage = static_cast<std::int32_t>(0.5 * dmg.damage_value);

        auto value_for_power = std::min<std::int32_t>(aura_power, half_damage);
        aura_power -= value_for_power;

        if (value_for_power > 0) {
            sender::send(make_action_message("destruction", game_board().index_for(entity_id)));

            auto enemy_id = dmg.damage_dealer_id;
            if (enemy_id != no_damage_dealer) {
                damage_dealers::standard_damage_dealer(magic_damage(value_for_power, enemy_id, entity_id));
            }
        }

    }, damage_taker::on_receive_damage_policy::after);
}
