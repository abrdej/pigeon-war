#pragma once

#include <turn_based/ability.h>
#include <turn_based/defs.h>

class stone_skin : public passive_ability {
 public:
  explicit stone_skin(entity_id_t entity_id);

 private:
  static constexpr auto name = "stone_skin";

  const entity_id_t entity_id_;
  int damage_reduction_{0};
  int reduction_increase_amount_{1};
};
