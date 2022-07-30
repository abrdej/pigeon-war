#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class tongue_of_fire final : public path_target_ability, per_turn_usable {
 public:
  explicit tongue_of_fire(std::uint32_t entity_id);

  ABILITY_TYPE(offensive)

 private:
  void use(std::uint32_t index_on) override;

 private:
  static constexpr auto name = "tongue_of_fire";
  const std::uint32_t entity_id_;
  std::int32_t damage_{9};
};
