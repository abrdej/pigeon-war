#pragma once

#include <turn_based/per_turn_usable.h>
#include <straight_target_ability.h>

class spear final : public straight_target_ability<1>, per_turn_usable
{
public:
  explicit spear(std::uint32_t id);

  bitmap_key get_name() const override {
    return "spear";
  }

  ability_types type() const override {
    return ability_types::offensive;
  }

  DEFINE_DESC(spear, damage, additional_damage, accumulated_damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t on_index) override;

private:
  const std::int32_t damage{6};
  const std::int32_t additional_damage{6};
  std::int32_t accumulated_damage{0};
  std::uint32_t entity_id;
};
