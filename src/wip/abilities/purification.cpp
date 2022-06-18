#include <purification.h>

#include <power_cost_ability.h>
#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>
#include <components/damage_taker.h>
#include <turn_based/sender.h>
#include <components/power_field.h>
#include <components/applied_effects.h>
#include <messages/massages_makers.h>

purification::purification(std::uint32_t entity_id)
  : path_target_ability(3, target_types::friendly),
    entity_id(entity_id) {}

void purification::use(std::uint32_t index_on) {

  if (used) {
    return;
  }

  if (!use_ability_at_the_expense_of_power(entity_id, power_cost)) {
    return;
  }

  auto friend_id = game_board().at(index_on);

  sender::send(make_action_message("purification", index_on));

  remove_negative_effects(friend_id);

  used = true;
}
