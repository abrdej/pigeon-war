#include <managers/entity_manager.h>
#include <core/game.h>
#include <components/power_field.h>
#include "massages_makers.h"
#include "messages/from_to_json.h"

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

std::string make_entities_names_message(const std::unordered_map<std::uint32_t, std::string>& names) {
    json data;
    data["entities_names"] = names;
    return data.dump();
}

std::string make_entities_healths_message(const std::unordered_map<std::uint32_t, std::int32_t>& healths) {
    json data;
    data["entities_healths"] = healths;
    return data.dump();
}

std::string make_entities_pack_message(const std::unordered_map<std::uint32_t,
        std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>& entities_pack) {
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

std::string make_end_turn_message(std::uint32_t active_player) {
    json data;
    data["end_turn"] = active_player;
    return data.dump();
}

std::string make_description_message(const std::string& desc) {
    json data;
    data["description"] = desc;
    return data.dump();
}

std::string make_effect_description_message(const std::string& desc) {
    json data;
    data["effect_description"] = desc;
    return data.dump();
}

std::string make_remove_entity_message(std::uint32_t entity_id) {
    json data;
    data["remove_entity"] = entity_id;
    return data.dump();
}

std::string make_create_entity_message(std::uint32_t entity_id,
                                       const std::string& name,
                                       std::int32_t health,
                                       std::int32_t power,
                                       std::uint32_t index) {
    json data;
    data["create_entity"] = entity_id;
    data["name"] = name;
    data["health"] = health;
    data["power"] = power;
    data["index"] = index;
    return data.dump();
}

std::string make_create_entity_message(std::uint32_t entity_id) {
    return make_create_entity_message(entity_id,
                                      game_get<entity_manager>().get(entity_id).name,
                                      game_get<entity_manager>().get(entity_id).get<health_field>()->health,
                                      game_get<entity_manager>().get(entity_id).contain<power_filed>() ?
                                      game_get<entity_manager>().get(entity_id).get<power_filed>()->power :
                                      0,
                                      game_get<board>().index_for(entity_id));
}

std::string make_move_entity_message(std::uint32_t entity_id,
                                     std::uint32_t from_index,
                                     std::uint32_t to_index) {
    json data;
    data["move_entity"] = entity_id;
    data["from_index"] = from_index;
    data["to_index"] = to_index;
    return data.dump();
}

std::string make_battle_end_message(std::uint32_t player_id) {
    json data;
    data["battle_end"] = player_id;
    return data.dump();
}
