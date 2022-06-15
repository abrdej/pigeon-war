#include <abilities/stone_skin.h>

#include <components/damage_taker.h>

stone_skin::stone_skin(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto damage = dmg.damage_value;

        if (damage > 0) {

            damage = std::max(1, dmg.damage_value - damage_reduction);

            damage = std::min(health_pack.health, damage);

            damage_reduction += reduction_increase_amount;

            LOG(debug) << "damage_reduction: " << damage_reduction;
        }

        health_pack.health -= damage;

        return damage;
    });
}
