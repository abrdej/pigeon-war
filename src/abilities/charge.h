#pragma once

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class charge final : public neighboring_target_ability<>,
                     turn_callback_helper {
public:
  explicit charge(std::uint32_t entity_id);
  bitmap_key get_bitmap_key() const override {
    return "charge";
  }

  DEFINE_DESC_ONE(charge, damage)

private:
  void use(std::uint32_t index_on) override;

  std::int32_t damage{12};
//  bool used{false};
//  bool exhausted{false};
  std::vector<std::uint32_t> attacked_enemies_;
};

