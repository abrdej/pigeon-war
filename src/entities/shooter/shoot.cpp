#include <shoot.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

shoot::shoot(entity_id_t entity_id)
    : directed_target_ability(name),
      entity_id_(entity_id),
      bullets_per_turn_(get_param_or_default("bullets_per_turn", bullets_per_turn_)),
      damage_(get_param_or_default("damage", damage_)),
      bullets_(get_param_or_default("bullets", bullets_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_, bullets_);

  on_every_two_turns_from_next([this]() {
    bullets_ = bullets_per_turn_;
  });

  LOG(debug) << "Shoot setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "bullets_per_turn: " << bullets_per_turn_;
  LOG(debug) << "damage: " << damage_;
  LOG(debug) << "bullets: " << bullets_;
}

bool shoot::usable() const {
  return bullets_ != 0;
}

void shoot::use(index_t on_index) {
  if (bullets_ == 0) {
    return;
  }
  --bullets_;

  sender::send(make_action_message(name, game_control().selected_index_, on_index));
  damage_dealers::standard_damage_dealer(ranged_damage(damage_, game_board().at(on_index), entity_id_));
}
