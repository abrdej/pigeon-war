#include "shield.h"

#include <components/damage_taker.h>

shield::shield(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        std::int32_t damage = dmg.damage_value;
        if (dmg.damage_type == damage_types::RANGED) {
            damage = static_cast<std::int32_t>(std::round(damage * range_attack_reduction));
        }

        auto final_damage = std::min(health_pack.health, damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}
