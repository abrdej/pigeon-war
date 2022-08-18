#include <tongue_of_fire.h>

#include <config.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/board.h>

tongue_of_fire::tongue_of_fire(entity_id_t entity_id)
    : path_target_ability(name, 7),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Tongue of fire setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void tongue_of_fire::use(index_t index_on) {
  if (used) {
    return;
  }

  sender::send(make_action_message("tongue_of_fire", game_control().selected_index, index_on));

  damage_dealers::standard_damage_dealer(ranged_damage(damage_, game_board().at(index_on), entity_id_));

  used = true;
}
