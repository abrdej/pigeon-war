#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class magic_bullet final : public path_target_ability, protected per_turn_callback {
 public:
  explicit magic_bullet(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(magic_bullet)

  std::string hint() const override;

  [[nodiscard]] bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on) override;

 private:
  std::uint32_t entity_id;
  std::int32_t magic_power_accumulation_amount{10};
  std::int32_t magic_power_drain_amount{4};
  bool used{false};
  bool first_used{false};
};
