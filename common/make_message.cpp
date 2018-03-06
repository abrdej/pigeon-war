#include "make_message.h"
#include "common/messages/messages.h"

using nlohmann::json;

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

std::string make_local_state_message(const local_state& state) {
    json data;
    data["local_state"] = state;
    return data.dump();
}

std::string make_game_state_message(const game_state& state) {
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