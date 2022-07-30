#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class magic_bullet final : public path_target_ability, protected per_turn_callback {
 public:
  explicit magic_bullet(entity_id_t entity_id);

  [[nodiscard]] bool usable() const override {
    return !used_;
  }

 private:
  void use(index_t index_on) override;

 private:
  static constexpr auto name = "magic_bullet";

  entity_id_t entity_id_;
  std::int32_t magic_power_accumulation_amount_{10};
  std::int32_t magic_power_drain_amount_{4};
  bool used_{false};
  bool first_used_{false};
};
