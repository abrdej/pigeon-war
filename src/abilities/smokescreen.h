#pragma once

#include <abilities/path_target_ability.h>

class smokescreen final : public path_target_ability {
public:
  explicit smokescreen(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(smokescreen)

  //DEFINE_DESC_ONE(smokescreen, damage_)

  bool usable() const override {
    return !used_;
  }

private:
  void use(std::uint32_t on_index) override;
  void set_smokescreen_effect(std::uint32_t enemy_id);

private:
  const std::uint32_t entity_id_;
  const std::int32_t range_reduction_{1};
  const std::int32_t duration_{2};
  bool used_{false};
};
