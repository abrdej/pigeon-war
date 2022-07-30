#include <turn_based/components/damage_taker.h>

#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

void play_change_health_animation(index_t to_index, entity_id_t entity_id,
                                  std::int32_t change_health) {
  sender::send(make_action_message("change_health", entity_id, change_health));
}

void play_power_change_animation(index_t to_index, std::int32_t change_power) {
  sender::send(make_action_message("change_power", game_board().at(to_index), change_power));
}

std::unordered_map<entity_id_t, std::int32_t> get_healths() {
  std::unordered_map<entity_id_t, std::int32_t> returned_map;
  game::get<entity_manager>().for_all([&returned_map](base_entity entity) {
    returned_map.insert(std::make_pair(entity.entity_id, entity.get<health_field>()->health));
  });
  return returned_map;
}
