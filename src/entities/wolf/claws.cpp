#include <claws.h>

#include <config.h>
#include <turn_based/board.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/messages/massages_makers.h>
#include <turn_based/sender.h>

claws::claws(id_t entity_id)
    : neighboring_target_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Claws setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void claws::use(std::uint32_t index_on) {
  if (used) {
    return;
  }

  sender::send(make_action_message("claws", entity_id_, index_on));

  auto enemy_id = game_board().at(index_on);

  damage_dealers::standard_damage_dealer(melee_damage(damage_, enemy_id, entity_id_));

  used = true;
}
