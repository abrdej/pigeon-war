#include <abilities/shield.h>

#include <components/damage_taker.h>
#include <effects/aura_of_armor_effect.h>
#include <effects/auras_observer.h>

shield::shield(std::uint32_t entity_id) : entity_id_(entity_id) {
  game::get<auras_observer>().add_aura(
    entity_id_, std::make_shared<aura_of_armor_effect>(entity_id_, aura_damage_reduction_));
}

void shield::use(std::uint32_t use_on_index) {
  if (used_) {
    return;
  }

  used_ = true;

  game::get<auras_observer>().remove_aura(entity_id_);

  set_damage_receiver(
    entity_id_, [this](health_field& health_pack, const damage_pack& dmg) mutable {
      std::int32_t damage = dmg.damage_value;
      //if (dmg.damage_type == damage_types::RANGED) {
        damage = damage - static_cast<std::int32_t>(std::round(damage * attack_reduction_));
      //}

      auto final_damage = std::min(health_pack.health, damage);
      health_pack.health -= final_damage;

      return final_damage;
    });
}
