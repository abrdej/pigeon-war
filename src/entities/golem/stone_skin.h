#pragma once

#include <turn_based/ability.h>

class stone_skin : public passive_ability {
 public:
  explicit stone_skin(std::uint32_t entity_id);

 private:
  static constexpr auto name = "stone_skin";

  int damage_reduction_{0};
  int reduction_increase_amount_{1};
};
