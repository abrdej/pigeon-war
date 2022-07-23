#pragma once

#include <turn_based/ability.h>

class armor : public passive_ability {
 public:
  explicit armor(std::uint32_t entity_id);

 private:
  static constexpr auto name = "armor";
  std::int32_t max_damage_{6};
};
