#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class warrior_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
  explicit warrior_blow(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(warrior_blow)

  DEFINE_DESC_ONE(warrior_blow, damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id;
  const std::int32_t damage = 10;
  const std::int32_t damage_per_factor = 2;
};
