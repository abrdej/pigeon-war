//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_POWER_BULLET_H
#define PIGEONWAR_POWER_BULLET_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class power_bullet final : public straight_target_ability<2>, per_turn_usable
{
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

private:
  const std::int32_t full_damage = 12;
  const std::int32_t damage_with_power_bullet_effect = 4;
  const std::int32_t duration_of_effect = 2;
};

#endif //PIGEONWAR_POWER_BULLET_H
