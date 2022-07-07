#include <sniper_shot.h>

#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/massages_makers.h>
#include <turn_based/sender.h>

void sniper_shot::prepare(std::uint32_t for_index) {
  game_control().selected_index_ = for_index;

  bool enemy_close = false;

  std::vector<std::uint32_t> neighbors;
  board_helper::neighboring_fields(for_index, neighbors, false);
  for (auto& neighbor_index : neighbors) {
    if (!game_board().empty(neighbor_index) && players_helpers::is_enemy_entity(neighbor_index)) {
      enemy_close = true;
      break;
    }
  }

  if (!enemy_close) {
    board_helper::calc_straight(for_index,
                                game_control().possible_movements_,
                                game_control().possible_movements_costs_,
                                range);

  } else {
    game_control().possible_movements_.clear();
    game_control().possible_movements_costs_.clear();
  }

  game_control().actual_targeting_type_ = target_types::enemy;
  game_control().wait_for_action([this](std::uint32_t index) { return use(index); });
}

void sniper_shot::use(std::uint32_t index_on) {
  if (used) return;

  auto used_from_index = game_control().selected_index_;
  auto entity_id = game_board().at(used_from_index);

  sender::send(make_action_message("sniper_shot", used_from_index, index_on));

  auto enemy_id = game_board().at(index_on);

  auto health_pack = game::get<entity_manager>().get(enemy_id).get<health_field>();
  float health_percent = health_pack->health / static_cast<float>(health_pack->base_health) * 100.f;

  LOG(debug) << "health_percent: " << health_percent;

  std::int32_t final_damage = damage;

  if (health_percent < 50.f) {
    final_damage += additional_damage;
  }

  damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

  used = true;
}

std::string sniper_shot::hint() const {
  std::string desc;
  desc = "Sniper Shot - deals damage of: " + std::to_string(damage)
      + ".\nIf the target is below 50% of health deals additional: " + std::to_string(damage)
      + " damage.\nSniper can't give a shot when the enemy unit is in his neighborhood.";
  "Range: " + std::to_string(range) + ".";

  return std::move(desc);
}
