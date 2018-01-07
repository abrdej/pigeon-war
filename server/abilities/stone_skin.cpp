#include "stone_skin.h"
#include "managers/health_manager.h"

stone_skin::stone_skin(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto damage = dmg.damage_value;

        if (damage > 0) {

            damage = std::max(1, dmg.damage_value - damage_reduction);

            damage = std::min(health_pack.health, damage);

            damage_reduction += reduction_increase_amount;

            std::cout << "damage_reduction: " << damage_reduction << "\n";
        }

        health_pack.health -= damage;

        return damage;
    });
}
