#pragma once

#include <abilities/ability.h>
#include <abilities/caster_target_ability.h>

class shield : public caster_target_ability {
 public:
  explicit shield(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(shield)

  DEFINE_DESC_ZERO(shield)

  void use(std::uint32_t use_on_index) override;

  bool usable() const override {
    return !used_;
  }

 private:
  std::uint32_t entity_id_;
  bool used_{false};
  float attack_reduction_{0.2f};
  std::int32_t aura_damage_reduction_{1};
};
