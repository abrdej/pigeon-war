#include <shoot.h>

#include <turn_based/damage_dealers.h>
#include <turn_based/board.h>
#include <logging/logger.h>
#include <turn_based/sender.h>
#include <turn_based/messages/massages_makers.h>

shoot::shoot(id_t entity_id)
    : configurable("shoot"),
      entity_id_(entity_id),
      bullets_per_turn_(get_param<decltype(bullets_per_turn_)>("bullets_per_turn")),
      damage_(get_param<decltype(damage_)>("damage")),
      bullets_(get_param<decltype(bullets_)>("bullets")) {

  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "bullets_per_turn: " << bullets_per_turn_;
  LOG(debug) << "damage: " << damage_;
  LOG(debug) << "bullets: " << bullets_;

  on_every_two_turns_from_next([this]() {
    bullets_ = bullets_per_turn_;
  });
}

void shoot::use(index_t on_index) {
  if (bullets_ == 0) {
    return;
  }
  --bullets_;

  sender::send(make_action_message("shoot", game_control().selected_index_, on_index));
  damage_dealers::standard_damage_dealer(ranged_damage(damage_, game_board().at(on_index), entity_id_));
}
