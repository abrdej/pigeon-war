#pragma once

#include <turn_based/ability.h>
#include <turn_based/configurable.h>
#include <turn_based/hint_configuration.h>

class armor : public passive_ability, private configurable {
 public:
  explicit armor(std::uint32_t entity_id);

 private:
  static constexpr auto name = "armor";
  std::int32_t max_damage_{6};
};
