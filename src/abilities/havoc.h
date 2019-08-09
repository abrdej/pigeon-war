#pragma once

#include "path_target_ability.h"
#include "per_turn_usable.h"

class havoc final : public path_target_ability {
public:
  explicit havoc(std::uint32_t entity_id);

  bitmap_key get_bitmap_key() const override {
    return "havoc";
  }

  ability_types type() const override {
    return ability_types::special;
  }

  DEFINE_DESC(havoc, damage, required_power)

  bool usable() const override;

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id;
  const std::int32_t damage = 20;
  const std::int32_t required_power = 20;
};
