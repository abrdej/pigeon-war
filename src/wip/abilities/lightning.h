#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class lightning : public path_target_ability, per_turn_usable {
public:
  explicit lightning(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(lightning)

  std::string hint() const override;

  bool usable() const override;

private:
  void use(std::uint32_t index_on) override;

  std::uint32_t entity_id_;
  std::int32_t damage_{12};
  std::int32_t power_cost_{10};
};
