#include <cleaver.h>

#include <turn_based/damage_dealers.h>
#include <components/power_field.h>
#include <turn_based/board.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

cleaver::cleaver(std::uint32_t entity_id) : entity_id(entity_id) {}

void cleaver::use(std::uint32_t index_on)
{
    if (used) {
        return;
    }
    auto power_module = game_get<entity_manager>().get(entity_id).get<power_filed>();
    if (power_module->power == 20) {
        return;
    }

    sender::send(make_action_message("cleaver", entity_id, index_on));

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

    auto power_charge_amount = change_power(*power_module, power_charge);

    LOG(debug) << "power_charge_amount: " << power_charge_amount;
    LOG(debug) << "power: " << power_module->power;

    sender::send(make_action_message("spectre_power_charging", entity_id, power_charge_amount));

    used = true;
}
