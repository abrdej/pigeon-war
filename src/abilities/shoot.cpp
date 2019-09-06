#include <abilities/shoot.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>

shoot::shoot(id_t entity_id) : entity_id_(entity_id) {
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
