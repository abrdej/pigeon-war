#pragma once

#include <turn_based/per_turn_usable.h>
#include <turn_based/straight_target_ability.h>

class power_bullet final : public straight_target_ability<2>, per_turn_usable {
 public:
  explicit power_bullet(std::uint32_t entity_id);

  ability_types type() const override {
    return ability_types::offensive;
  }

  bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on) override;

  static constexpr auto name = "power_bullet";

  std::uint32_t entity_id_;
  std::int32_t full_damage_ = 12;
  std::int32_t damage_with_power_bullet_effect_ = 4;
  std::int32_t duration_of_effect_ = 2;
};
