#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class claws final : public neighboring_target_ability<>, per_turn_usable {
 public:
  explicit claws(entity_id_t entity_id);

  [[nodiscard]] ability_types type() const override {
    return ability_types::offensive;
  }

 private:
  void use(index_t index_on) override;

 private:
  static constexpr auto name = "claws";
  const entity_id_t entity_id_;
  std::int32_t damage_{4};
};
