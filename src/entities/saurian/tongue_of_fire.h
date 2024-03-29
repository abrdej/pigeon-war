#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class tongue_of_fire final : public path_target_ability, per_turn_usable {
 public:
  explicit tongue_of_fire(entity_id_t entity_id);

  [[nodiscard]] ability_types type() const override {
    return ability_types::offensive;
  }

 private:
  void use(index_t index_on) override;

 private:
  static constexpr auto name = "tongue_of_fire";
  const entity_id_t entity_id_;
  std::int32_t damage_{9};
};
