#include <havoc.h>

#include <turn_based/damage_dealers.h>
#include <components/power_field.h>
#include <turn_based/board.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

havoc::havoc(std::uint32_t entity_id)
  : path_target_ability(6), entity_id(entity_id) {}

bool havoc::usable() const {
  auto& power = game_get<entity_manager>().get(entity_id).get<power_filed>()->power;
  return power >= required_power;
}

void havoc::use(std::uint32_t index_on) {
  auto& power = game_get<entity_manager>().get(entity_id).get<power_filed>()->power;
  if (power < required_power) {
    return;
  }

  power = 0;
  sender::send(make_action_message("havoc", game_control().selected_index_, index_on));

  auto enemy_id = game_board().at(index_on);

  damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, entity_id));
}
