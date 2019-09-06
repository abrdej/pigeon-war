#pragma once

#include <abilities/straight_target_ability.h>
#include <abilities/per_turn_usable.h>

class sparks final : public straight_target_ability<1>,
                      per_turn_usable {
public:
  explicit sparks(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(sparks)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t on_index) override;

private:
  std::uint32_t entity_id_;
};
