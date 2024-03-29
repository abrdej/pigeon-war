#include <get_entity_names.h>

#include <turn_based/game.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>

std::unordered_map<entity_id_t, std::string> get_entity_names() {
  std::unordered_map<entity_id_t, std::string> entity_names;
  game::get<entity_manager>().for_all([&entity_names](const base_entity& entity) {
    entity_names.emplace(entity.entity_id, entity.name);
  });
  return entity_names;
}

std::unordered_map<entity_id_t, std::uint32_t> get_entity_players() {
  std::unordered_map<entity_id_t, std::uint32_t> entity_players;
  game::get<entity_manager>().for_all([&entity_players](const base_entity& entity) {
    const auto player_id = game::get<players_manager>().player_for_entity(entity.entity_id);
    entity_players.emplace(entity.entity_id, player_id);
  });
  return entity_players;
};
