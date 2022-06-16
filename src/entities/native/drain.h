#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class drain final : public neighboring_target_ability<>, per_turn_usable {
 public:
  explicit drain(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(drain)

  DEFINE_DESC(drain, damage, drain_amount)

  bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on) override;

 private:
  const std::uint32_t entity_id;
  const std::int32_t damage = 10;
  const std::int32_t drain_amount = 4;
};
