#pragma once

#include <abilities/ability.h>
#include <abilities/per_turn_usable.h>

class sniper_shot final : public active_ability, per_turn_usable {
public:
  ADD_BITMAP_GETTER(sniper_bullet)

  std::string hint() const override;

  bool usable() const override {
    return !used;
  }

private:
  void prepare(std::uint32_t for_index) override;

  void use(std::uint32_t index_on);

private:
  const std::int32_t range{10};
  const std::int32_t damage{12};
  const std::int32_t additional_damage{12};
};
