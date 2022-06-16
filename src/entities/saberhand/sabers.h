#pragma once

#include <vector>

#include "abilities/ability.h"
#include "abilities/per_turn_usable.h"
#include "core/configurable.h"

class sabers final : public active_ability, per_turn_usable, configurable {
 public:
  explicit sabers(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(sabers)

  DEFINE_DESC_ONE(sabers, damage_)

  [[nodiscard]] bool usable() const override {
    return !used;
  }

 private:
  void prepare(std::uint32_t for_index) override;
  void target(std::uint32_t on);
  void use(std::uint32_t index_on);

  const std::uint32_t entity_id_;
  const std::int32_t damage_ = 7;
  std::vector<std::uint32_t> targets_;
};
