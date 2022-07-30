#pragma once

#include <turn_based/ability.h>
#include <turn_based/defs.h>

class armor : public passive_ability {
 public:
  explicit armor(entity_id_t entity_id);

 private:
  static constexpr auto name = "armor";
  const std::int32_t max_damage_{6};
};
