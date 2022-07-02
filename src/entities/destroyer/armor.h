#pragma once

#include <turn_based/ability.h>

class armor : public passive_ability {
 public:
  explicit armor(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(armor)

  DEFINE_DESC_ONE(armor, max_damage)

 private:
  std::int32_t max_damage{6};
};
