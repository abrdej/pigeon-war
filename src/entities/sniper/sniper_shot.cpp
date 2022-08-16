#include <sniper_shot.h>

#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/components/health_field.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

sniper_shot::sniper_shot(entity_id_t entity_id)
    : active_ability(name),
      entity_id_(entity_id),
      range_(get_param_or_default("range", range_)),
      damage_(get_param_or_default("damage", damage_)),
      additional_damage_(get_param_or_default("additional_damage", additional_damage_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_, additional_damage_, range_);

  LOG(debug) << "Sniper shot setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "range: " << range_;
  LOG(debug) << "damage: " << damage_;
  LOG(debug) << "additional_damage: " << additional_damage_;
}

void sniper_shot::prepare(index_t for_index) {
  game_control().selected_index_ = for_index;

  bool enemy_close = false;

  std::vector<index_t> neighbors;
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
                                range_);

  } else {
    game_control().possible_movements_.clear();
    game_control().possible_movements_costs_.clear();
  }

  game_control().actual_targeting_type_ = target_types::enemy;
  game_control().wait_for_action([this](index_t index) { return use(index); });
}

void sniper_shot::use(index_t index_on) {
  if (used) return;

  auto used_from_index = game_control().selected_index_;
  auto entity_id = game_board().at(used_from_index);

  sender::send(make_action_message(name, used_from_index, index_on));

  auto enemy_id = game_board().at(index_on);

  auto health_pack = game::get<entity_manager>().get(enemy_id).get<health_field>();
  float health_percent = health_pack->health / static_cast<float>(health_pack->base_health) * 100.f;

  LOG(debug) << "health_percent: " << health_percent;

  std::int32_t final_damage = damage_;

  if (health_percent < 50.f) {
    final_damage += additional_damage_;
  }

  damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

  used = true;
}
