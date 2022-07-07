#pragma once

#include <turn_based/per_turn_usable.h>
#include <turn_based/straight_target_ability.h>

class power_bullet final : public straight_target_ability<2>, per_turn_usable {
 public:
  bitmap_key get_bitmap_key() const override {
    return "power_bullet";
  }
  ability_types type() const override {
    return ability_types::offensive;
  }

  std::string hint() const override;

  bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on) override;

  const std::int32_t full_damage = 12;
  const std::int32_t damage_with_power_bullet_effect = 4;
  const std::int32_t duration_of_effect = 2;
};
