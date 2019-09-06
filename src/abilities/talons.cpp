#include <abilities/talons.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>

talons::talons(std::uint32_t entity_id) : entity_id_(entity_id) {
  on_every_two_turns_from_next([this]() {
    used = false;
    trash_trail_enemy_id_ = none_entity_id;
  });
}

void talons::use(std::uint32_t index_on) {
  if (used) {
    return;
  }

  auto damage = damage_;
  if (trash_trail_enemy_id_ != none_entity_id) {
    auto enemy_id = game_board().at(index_on);
    if (enemy_id == trash_trail_enemy_id_) {
      damage += damage_boost_for_trash_trail_;
    }
  }

  sender::send(make_action_message("talons", entity_id_, index_on));

  damage_dealers::standard_damage_dealer(melee_damage(damage, game_board().at(index_on), entity_id_));

  used = true;
}
