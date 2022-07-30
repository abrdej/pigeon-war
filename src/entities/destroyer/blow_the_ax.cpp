#include <blow_the_ax.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

blow_the_ax::blow_the_ax(entity_id_t entity_id)
    : straight_target_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Blow the ax setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void blow_the_ax::use(std::uint32_t on_index) {
  if (used) {
    return;
  }

  sender::send(make_action_message(name, entity_id_, on_index));
  damage_dealers::standard_damage_dealer(melee_damage(damage_, game_board().at(on_index), entity_id_));

  used = true;
}
