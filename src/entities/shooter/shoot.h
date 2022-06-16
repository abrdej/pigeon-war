#pragma once

#include "abilities/per_turn_usable.h"
#include "abilities/straight_target_ability.h"
#include "core/configurable.h"
#include "core/defs.h"

class shoot final : public directed_target_ability<3>, protected per_turn_callback, protected configurable {
 public:
  explicit shoot(id_t entity_id);

  ADD_BITMAP_GETTER(bullet)

  DEFINE_DESC(shoot, damage_, bullets_)

  [[nodiscard]] bool usable() const override {
    return bullets_ != 0;
  }

 private:
  void use(index_t on_index) override;

  const id_t entity_id_;
  const std::int32_t bullets_per_turn_{2};
  const std::int32_t damage_{6};
  std::int32_t bullets_{bullets_per_turn_};
};
