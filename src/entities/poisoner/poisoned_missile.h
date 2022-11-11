#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class poisoned_missile final : public path_target_ability, per_turn_usable {
 public:
  explicit poisoned_missile(entity_id_t entity_id);

  [[nodiscard]] bool usable() const override {
    return !used;
  }

 private:
  void use(index_t index_on) override;

 private:
  static constexpr auto name = "poisoned_missile";
  entity_id_t entity_id_;
  const std::int32_t damage_{6};
  const std::int32_t poison_power_{5};
  const std::int32_t poison_duration_{3};
};
