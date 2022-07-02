#include <armor.h>

#include <turn_based/components/damage_taker.h>

armor::armor(std::uint32_t entity_id) {
  set_damage_receiver(
      entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {
        auto final_damage = std::min(std::min(health_pack.health, dmg.damage_value), max_damage);
        health_pack.health -= final_damage;
        return final_damage;
      });
}
