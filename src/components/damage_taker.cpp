#include "damage_taker.h"
#include <messages/massages_makers.h>
#include <server/sender.h>

void play_change_health_animation(std::uint32_t to_index, std::uint32_t entity_id,
                                  std::int32_t change_health) {
  sender::send(make_action_message("change_health", entity_id, change_health));
}

void play_power_change_animation(std::uint32_t to_index, std::int32_t change_power) {
  sender::send(make_action_message("change_power", game_board().at(to_index), change_power));
}

std::unordered_map<std::uint32_t, std::int32_t> get_healths() {
  std::unordered_map<std::uint32_t, std::int32_t> returned_map;
  game::get<entity_manager>().for_all([&returned_map](base_entity entity) {
    returned_map.insert(std::make_pair(entity.entity_id, entity.get<health_field>()->health));
  });
  return std::move(returned_map);
}