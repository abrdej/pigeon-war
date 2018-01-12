#include <managers/health_manager.h>
#include "shield.h"

shield::shield(sf::Uint64 entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        sf::Int32 damage = dmg.damage_value;
        if (dmg.damage_type == damage_types::RANGED) {
            damage = static_cast<sf::Int32>(std::round(damage * range_attack_reduction));
        }

        auto final_damage = std::min(health_pack.health, damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

std::string shield::hint() const {

    std::string desc;
    desc = "Shield - guardian receive only 50% percent from ranged damage.\n";

    return std::move(desc);
}