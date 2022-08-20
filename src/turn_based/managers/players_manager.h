#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <turn_based/defs.h>

//enum players_ids : player_id_t {
//  neutral_id = std::numeric_limits<std::uint32_t>::max(),
//  no_player_id = std::numeric_limits<std::uint32_t>::max() - 1,
//  destructive_surroundings_id = std::numeric_limits<std::uint32_t>::max() - 2
//};

namespace players_ids {
static constexpr player_id_t neutral_id{std::numeric_limits<player_id_t::value_type>::max()};
static constexpr player_id_t no_player_id{std::numeric_limits<player_id_t::value_type>::max() - 1};
static constexpr player_id_t destructive_surroundings_id{std::numeric_limits<player_id_t::value_type>::max() - 2};
}

class players_manager {
 public:
  player_id_t create_human_player(const std::string& player_name) {
    players.emplace_back(std::make_pair(player_name, false));
    return static_cast<player_id_t>(players.size() - 1);
  }

  player_id_t create_ai_player(const std::string& player_name) {
    players.emplace_back(std::make_pair(player_name, true));
    return static_cast<player_id_t>(players.size() - 1);
  }

  void add_entity_for_player(player_id_t player_id, entity_id_t entity_id) {
    entity_id_to_player_id[entity_id] = player_id;
  }

  void add_neutral_entity(entity_id_t entity_id) {
    entity_id_to_player_id[entity_id] = players_ids::neutral_id;
  }

  void add_destructive_surroundings(entity_id_t entity_id) {
    entity_id_to_player_id[entity_id] = players_ids::destructive_surroundings_id;
  }

  bool player_entity(player_id_t player_id, entity_id_t entity_id) {
    return entity_id_to_player_id[entity_id] == player_id;
  }
  bool active_player_entity(entity_id_t entity_id) {
    return entity_id_to_player_id[entity_id] == active_player_id;
  }

  bool enemy_entity(player_id_t player_id, entity_id_t entity_id) {
    return entity_id_to_player_id[entity_id] != player_id
        && entity_id_to_player_id[entity_id] != players_ids::neutral_id;
  }

  bool neutral_entity(entity_id_t entity_id) {
    return entity_id_to_player_id[entity_id] == players_ids::neutral_id;
  }

  std::string player_name(player_id_t player_id) { return players[player_id.cast()].first; }

  player_id_t player_for_entity(entity_id_t entity_id) {
    auto it = entity_id_to_player_id.find(entity_id);
    if (it != std::end(entity_id_to_player_id)) {
      return it->second;
    } else {
      return players_ids::no_player_id;
    }
  }

  player_id_t get_active_player_id() const { return active_player_id; }

  player_id_t next_player() {
    auto id = active_player_id.cast();
    auto next_player_id = static_cast<player_id_t>(++id % players.size());
    active_player_id = next_player_id;
    return next_player_id;
  }

  bool is_active_player_ai() { return players[active_player_id.cast()].second; }

 private:
  std::vector<std::pair<std::string, bool>> players;
  std::unordered_map<entity_id_t, player_id_t> entity_id_to_player_id;
  player_id_t active_player_id{0};
};

namespace players_helpers {

void player_entities_indexes(player_id_t player_id, std::vector<index_t>& indexes);
void enemy_entities_indexes(player_id_t player_id, std::vector<index_t>& indexes);

bool is_player_entity(index_t entity_index);
bool is_enemy_entity(index_t entity_index);
bool is_neutral_entity(index_t entity_index);
index_t active_player_first_entity_index();

}  // namespace players_helpers
