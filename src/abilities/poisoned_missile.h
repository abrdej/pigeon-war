//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_POISONED_MISSILE_H
#define PIGEONWAR_POISONED_MISSILE_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class poisoned_missile final : public path_target_ability<4>, per_turn_usable
{
public:

  bitmap_key get_bitmap_key() const override {
    return "poisoned_missile";
  }

  std::string hint() const override;

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::int32_t damage{6};
  const std::int32_t poison_power{5};
  const std::int32_t poison_duration{3};
};

#endif //PIGEONWAR_POISONED_MISSILE_H
