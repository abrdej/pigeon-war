#pragma once

#include <unordered_map>

#include <external/json.hpp>

#include <core/game_state.h>

std::string make_map_size_message(const std::pair<std::uint32_t, std::uint32_t>& map_size);

std::string make_client_id_message(std::uint32_t client_id);

std::string make_map_name_message(const std::string& map_name);

template <std::size_t N>
std::string make_board_message(const std::array<std::vector<std::uint32_t>, N> board_fields) {
  using nlohmann::json;
  json data;
  data["board"] = board_fields;
  return data.dump();
}

std::string make_entities_names_message(
    const std::unordered_map<std::uint32_t, std::string>& names);

std::string make_entities_healths_message(
    const std::unordered_map<std::uint32_t, std::int32_t>& healths);

std::string make_entities_pack_message(
    const std::unordered_map<std::uint32_t,
                             std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>&
        entities_pack);

std::string make_local_game_state_message(const local_game_state& state);

std::string make_global_game_state_message(const global_game_state& state);

std::string make_end_turn_message(std::uint32_t active_player);

std::string make_description_message(const std::string& desc);

std::string make_effect_description_message(const std::string& desc);

std::string make_remove_entity_message(std::uint32_t entity_id);

std::string make_create_entity_message(std::uint32_t entity_id, const std::string& name,
                                       std::int32_t health, std::int32_t power,
                                       std::uint32_t index);

std::string make_create_entity_message(std::uint32_t entity_id);

std::string make_move_entity_message(std::uint32_t entity_id, std::uint32_t from_index,
                                     std::uint32_t to_index);

std::string make_battle_end_message(std::uint32_t player_id);

template <typename... Args>
std::string make_action_message(const std::string& animation, Args&&... args) {
  using nlohmann::json;
  json array_of_data;

  array_of_data.emplace_back(animation);

  auto packer = [&array_of_data](auto x) { array_of_data.emplace_back(x); };

  std::int32_t tab[] = {(packer(std::forward<Args>(args)), 0)...};

  json data;
  data["animation"] = array_of_data;
  return data.dump();
}
