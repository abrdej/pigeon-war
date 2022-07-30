#include <stone_skin.h>

#include <logging/logger.h>
#include <turn_based/components/damage_taker.h>

stone_skin::stone_skin(entity_id_t entity_id)
    : passive_ability(name),
      entity_id_(entity_id),
      damage_reduction_(get_param_or_default("initial_damage_reduction", damage_reduction_)),
      reduction_increase_amount_(get_param_or_default("reduction_increase_amount", reduction_increase_amount_)) {
  set_damage_receiver(entity_id, [this](health_field& health_pack, const damage_pack& dmg) mutable {
    auto damage = dmg.damage_value;
    if (damage > 0) {
      damage = std::max(1, dmg.damage_value - damage_reduction_);
      damage = std::min(health_pack.health, damage);
      damage_reduction_ += reduction_increase_amount_;
      LOG(debug) << "damage_reduction: " << damage_reduction_;
    }
    health_pack.health -= damage;
    return damage;
  });

  configure_hint(config_directory + name + ".json", "hint", reduction_increase_amount_, damage_reduction_);

  LOG(debug) << "Power bullet setup:";
  LOG(debug) << "entity_id: " << entity_id;
  LOG(debug) << "damage_reduction: " << damage_reduction_;
  LOG(debug) << "reduction_increase_amount: " << reduction_increase_amount_;
}
