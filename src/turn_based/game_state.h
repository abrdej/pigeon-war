#pragma once

#include <deque>
#include <unordered_map>
#include <unordered_set>

#include <json.hpp>

#include <turn_based/bitmap_key.h>
#include <turn_based/defs.h>
#include <turn_based/states.h>

struct global_game_state {
  std::vector<std::deque<entity_id_t>> board;
  std::unordered_map<entity_id_t, std::int32_t> healths;
  std::unordered_map<entity_id_t, std::string> entities_names;
  std::unordered_map<entity_id_t, std::uint32_t> entities_players;
  std::unordered_map<entity_id_t, std::vector<std::string>> entities_additional_effects;
};

struct local_game_state {
  std::vector<index_t> possible_movements;
  std::unordered_set<index_t> valid_movements;
  index_t selected_index{null_index};
  target_types actual_target_type{target_types::non};
  std::array<std::string, 5> button_bitmaps;
  std::array<bool, 5> usable;
  std::string entity_name;
};
