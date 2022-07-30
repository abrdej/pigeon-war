#include <armor.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/components/damage_taker.h>

armor::armor(entity_id_t entity_id)
    : passive_ability("armor"),
      max_damage_(get_param_or_default("max_damage", max_damage_)) {

  set_damage_receiver(
      entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {
        auto final_damage = std::min(std::min(health_pack.health, dmg.damage_value), max_damage_);
        health_pack.health -= final_damage;
        return final_damage;
      });

  configure_hint(config_directory + name + ".json", "hint", max_damage_);

  LOG(debug) << "Armor setup:";
  LOG(debug) << "entity_id: " << entity_id;
  LOG(debug) << "max_damage: " << max_damage_;
  LOG(debug) << "name: " << name;
}
