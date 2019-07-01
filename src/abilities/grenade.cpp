#include <abilities/grenade.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>

grenade::grenade(std::uint32_t entity_id) : entity_id_(entity_id) {}

void grenade::use(std::uint32_t on_index) {
  if (used_)
    return;

  used_ = true;

  std::vector<std::uint32_t> neighbors;
  board_helper::neighboring_fields(on_index, neighbors, false);

  sender::send(make_action_message("grenade", game_control().selected_index_, on_index));

  damage_dealers::standard_damage_dealer(ranged_damage(damage_, game_board().at(on_index), entity_id_));

  for (auto index : neighbors) {
    if (!game_board().empty(index)) {
      damage_dealers::standard_damage_dealer(ranged_damage(damage_ / 2, game_board().at(index), entity_id_));
    }
  }
}
