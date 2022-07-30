#pragma once

#include <config.h>
#include <turn_based/ability.h>
#include <turn_based/per_turn_usable.h>

class counterattack final : public passive_ability, per_turn_usable {
 public:
  explicit counterattack(entity_id_t entity_id);

 private:
  void use(std::uint32_t index_on);

  static constexpr auto name = "counterattack";
  const entity_id_t entity_id_;
  const std::int32_t damage_{10};
};
