#pragma once

#include <abilities/path_target_ability.h>
#include <abilities/per_turn_usable.h>

class lightning : public path_target_ability, per_turn_usable {
public:
  explicit lightning(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(lightning)

  std::string hint() const override;

private:
  void use(std::uint32_t index_on) override;

  std::uint32_t entity_id;
  std::int32_t damage{12};
  std::int32_t power_cost{10};
};
