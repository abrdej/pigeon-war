#pragma once

#include <abilities/straight_target_ability.h>
#include <abilities/per_turn_usable.h>

class eye_shoot final : public straight_target_ability<3>, per_turn_usable {
public:
  eye_shoot() = default;

  ADD_BITMAP_GETTER(eye_shoot)

  DEFINE_DESC(eye_shoot, base_damage, side_damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t to_index) override;

private:
  const std::int32_t base_damage{8};
  const std::int32_t side_damage{16};
};
