#pragma once

#include <abilities/path_target_ability.h>

class grenade final : public path_target_ability<3> {
public:
  explicit grenade(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(grenade)

  DEFINE_DESC_ONE(grenade, damage_)

  bool usable() const override {
    return !used_;
  }

private:
  void use(std::uint32_t on_index) override;

private:
  const std::uint32_t entity_id_;
  const std::int32_t damage_{12};
  bool used_{false};
};
