#pragma once

#include <abilities/path_target_ability.h>
#include <abilities/per_turn_usable.h>

class tongue_of_fire final : public path_target_ability, per_turn_usable {
public:
  explicit tongue_of_fire(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(tongue_of_fire)

  ABILITY_TYPE(offensive)

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id;
  const std::int32_t damage = 9;
};
