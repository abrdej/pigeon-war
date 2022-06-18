#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class poisoned_missile final : public path_target_ability, per_turn_usable
{
public:
  explicit poisoned_missile(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(poisoned_missile)

  std::string hint() const override;

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::int32_t damage_{6};
  const std::int32_t poison_power_{5};
  const std::int32_t poison_duration_{3};
};
