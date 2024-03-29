#include <turn_based/board.h>
#include <turn_based/components/health_field.h>
#include <turn_based/components/power_field.h>
#include <turn_based/defs.h>
#include <turn_based/game.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/from_to_json.h>
#include <turn_based/messages/messages_makers.h>

using nlohmann::json;

std::string make_map_size_message(const std::pair<std::uint32_t, std::uint32_t>& map_size) {
  json data;
  data["map_size"] = map_size;
  return data.dump();
}

std::string make_client_id_message(std::uint32_t client_id) {
  json data;
  data["client_id"] = client_id;
  return data.dump();
}

std::string make_map_name_message(const std::string& map_name) {
  json data;
  data["map_name"] = map_name;
  return data.dump();
}

std::string make_entities_names_message(
    const std::unordered_map<std::uint32_t, std::string>& names) {
  json data;
  data["entities_names"] = names;
  return data.dump();
}

std::string make_entities_healths_message(
    const std::unordered_map<std::uint32_t, std::int32_t>& healths) {
  json data;
  data["entities_healths"] = healths;
  return data.dump();
}

std::string make_entities_pack_message(
    const std::unordered_map<entity_id_t,
                             std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>&
        entities_pack) {
  json data;
  data["entities_pack"] = entities_pack;
  return data.dump();
}

std::string make_local_game_state_message(const local_game_state& state) {
  json data;
  data["local_state"] = state;
  return data.dump();
}

std::string make_global_game_state_message(const global_game_state& state) {
  json data;
  data["game_state"] = state;
  return data.dump();
}

std::string make_end_turn_message(player_id_t active_player) {
  json data;
  data["end_turn"] = active_player.cast();
  return data.dump();
}

std::string make_hint_message(const std::string& hint) {
  json data;
  data["hint"] = hint;
  return data.dump();
}

std::string make_description_message(const std::string& desc) {
  json data;
  data["description"] = desc;
  return data.dump();
}

std::string make_entity_description_message(const std::string& desc) {
  json data;
  data["entity_description"] = desc;
  return data.dump();
}

std::string make_effect_description_message(const std::string& desc) {
  json data;
  data["effect_description"] = desc;
  return data.dump();
}

std::string make_remove_entity_message(entity_id_t entity_id) {
  json data;
  data["remove_entity"] = entity_id.cast();
  return data.dump();
}

std::string make_create_entity_message(entity_id_t entity_id, const std::string& name,
                                       std::int32_t health, std::int32_t power,
                                       index_t index) {
  json data;
  data["create_entity"] = entity_id.cast();
  data["name"] = name;
  data["health"] = health;
  data["power"] = power;
  data["index"] = index;
  return data.dump();
}

std::string make_create_entity_message(entity_id_t entity_id) {
  return make_create_entity_message(
      entity_id, game_get<entity_manager>().get(entity_id).name,
      game_get<entity_manager>().get(entity_id).get<health_field>()->health,
      game_get<entity_manager>().get(entity_id).contain<power_filed>()
          ? game_get<entity_manager>().get(entity_id).get<power_filed>()->power
          : 0,
      game_get<board>().index_for(entity_id));
}

std::string make_move_entity_message(entity_id_t entity_id, index_t from_index, index_t to_index) {
  json data;
  data["move_entity"]["move_entity"] = entity_id.cast();
  data["move_entity"]["from_index"] = from_index;
  data["move_entity"]["to_index"] = to_index;
  return data.dump();
}

std::string make_battle_end_message(std::uint32_t player_id) {
  json data;
  data["battle_end"] = player_id;
  return data.dump();
}

std::string make_victory_message() {
  json data;
  data["victory"];
  return data.dump();
}

std::string make_defeat_message() {
  json data;
  data["defeat"];
  return data.dump();
}

std::string make_entity_talk_message(index_t index, std::string text) {
  json data;
  data["entity_talk"] = index;
  data["text"] = text;
  return data.dump();
}

std::string make_game_ready_message() {
  json data;
  data["game_ready"];
  return data.dump();
}
