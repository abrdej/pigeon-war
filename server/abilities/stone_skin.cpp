#include "stone_skin.h"
#include "components/damage_taker.h"

stone_skin::stone_skin(std::uint64_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

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

std::string stone_skin::hint() const {

    std::string desc;
    desc = "Stone Skin - with each received attack golem\n"
                   "increase his damage reduction by " + std::to_string(reduction_increase_amount) + " points.\n"
            "Current damage reduction: " + std::to_string(damage_reduction) + ".";

    return std::move(desc);
}