#include <grenade.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/board_helpers.h>
#include <turn_based/damage_dealers.h>

grenade::grenade(entity_id_t entity_id)
    : path_target_ability(name, 3),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Grenade setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

bool grenade::usable() const {
  return !used_;
}

void grenade::use(index_t on_index) {
  if (used_)
    return;

  used_ = true;

  std::vector<index_t> neighbors;
  board_helpers::neighboring_fields(on_index, neighbors, false);

  sender::send(make_action_message("grenade", game_control().selected_index, on_index));

  damage_dealers::standard_damage_dealer(ranged_damage(damage_, game_board().at(on_index), entity_id_));

  for (auto index : neighbors) {
    if (!game_board().empty(index)) {
      damage_dealers::standard_damage_dealer(ranged_damage(damage_ / 2, game_board().at(index), entity_id_));
    }
  }
}
