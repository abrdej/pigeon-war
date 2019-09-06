#include <abilities/sparks.h>

#include <abilities/abilities.h>
#include <abilities/damage_dealers.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <core/board.h>
#include <components/power_field.h>

sparks::sparks(std::uint32_t entity_id) : entity_id_(entity_id) {
  set_damage_receiver(entity_id, [entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

    auto power_burn = std::min<std::int32_t>(power->power, dmg.damage_value);
    power->power -= power_burn;
    sender::send(make_action_message("change_power", entity_id, -power_burn));

    auto damage = std::min(health_pack.health, dmg.damage_value - power_burn);
    health_pack.health -= damage;

    return damage;
  });
}

void sparks::use(std::uint32_t on_index) {

}
