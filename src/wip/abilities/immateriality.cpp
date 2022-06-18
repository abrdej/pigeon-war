#include <immateriality.h>

#include <components/damage_taker.h>

immateriality::immateriality(std::uint32_t entity_id) {
    on_every_two_turns_from_this([this, entity_id]() {
        is_active = true;
    });

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        if (is_active) {
            is_active = false;
            return 0;

        } else {
            auto final_damage = std::min(health_pack.health, dmg.damage_value);
            health_pack.health -= final_damage;

            return final_damage;
        }
    });
}
