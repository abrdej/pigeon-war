#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum players_ids : std::uint32_t {
  neutral_id = std::numeric_limits<std::uint32_t>::max(),
  no_player_id = std::numeric_limits<std::uint32_t>::max() - 1,
  destructive_surroundings_id = std::numeric_limits<std::uint32_t>::max() - 2
};

class players_manager {
 public:
  std::uint32_t create_human_player(const std::string& player_name) {
    players.emplace_back(std::make_pair(player_name, false));
    return static_cast<std::uint32_t>(players.size() - 1);
  }

  std::uint32_t create_ai_player(const std::string& player_name) {
    players.emplace_back(std::make_pair(player_name, true));
    return static_cast<std::uint32_t>(players.size() - 1);
  }

  void add_entity_for_player(std::uint32_t player_id, std::uint32_t entity_id) {
    entity_id_to_player_id[entity_id] = player_id;
  }

  void add_neutral_entity(std::uint32_t entity_id) {
    entity_id_to_player_id[entity_id] = players_ids::neutral_id;
  }

  void add_destructive_surroundings(std::uint32_t entity_id) {
    entity_id_to_player_id[entity_id] = players_ids::destructive_surroundings_id;
  }

  bool player_entity(std::uint32_t player_id, std::uint32_t entity_id) {
    return entity_id_to_player_id[entity_id] == player_id;
  }
  bool active_player_entity(std::uint32_t entity_id) {
    return entity_id_to_player_id[entity_id] == active_player_id;
  }

  bool enemy_entity(std::uint32_t player_id, std::uint32_t entity_id) {
    return entity_id_to_player_id[entity_id] != player_id
        && entity_id_to_player_id[entity_id] != players_ids::neutral_id;
  }

  bool neutral_entity(std::uint32_t entity_id) {
    return entity_id_to_player_id[entity_id] == players_ids::neutral_id;
  }

  std::string player_name(std::uint32_t player_id) { return players[player_id].first; }

  std::uint32_t player_for_entity(std::uint32_t entity_id) {
    auto it = entity_id_to_player_id.find(entity_id);
    if (it != std::end(entity_id_to_player_id)) {
      return it->second;
    } else {
      return players_ids::no_player_id;
    }
  }

  std::uint32_t get_active_player_id() { return active_player_id; }

  std::uint32_t next_player() {
    auto next_player_id = static_cast<std::uint32_t>(++active_player_id % players.size());
    active_player_id = next_player_id;
    return next_player_id;
  }

  bool is_active_player_ai() { return players[active_player_id].second; }

 private:
  std::vector<std::pair<std::string, bool>> players;
  std::unordered_map<std::uint32_t, std::uint32_t> entity_id_to_player_id;
  std::uint32_t active_player_id{0};
};

namespace players_helpers {

void player_entities_indexes(std::uint32_t player_id, std::vector<std::uint32_t>& indexes);
void enemy_entities_indexes(std::uint32_t player_id, std::vector<std::uint32_t>& indexes);

bool is_player_entity(std::uint32_t entity_index);
bool is_enemy_entity(std::uint32_t entity_index);
bool is_neutral_entity(std::uint32_t entity_index);
std::uint32_t active_player_first_entity_index();

}  // namespace players_helpers
