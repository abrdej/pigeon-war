#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class sword_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
  explicit sword_blow(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(sword_blow)
  DEFINE_DESC_ONE(sword_blow, damage_)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id_;
  const std::int32_t damage_ = 10;
};
