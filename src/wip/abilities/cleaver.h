#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class cleaver final : public neighboring_target_ability<>, per_turn_usable
{
public:
  explicit cleaver(std::uint32_t entity_id);
  bitmap_key get_name() const override {
    return "cleaver";
  }
  ability_types type() const override {
    return ability_types::offensive;
  }

  DEFINE_DESC_ONE(cleaver, damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id;
  const std::int32_t damage = 8;
  const std::int32_t power_charge = 5;
};
