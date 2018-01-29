#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <SFML/Config.hpp>

class entity;

class players_manager {

	static std::unique_ptr<players_manager> impl;

	static players_manager& get_instance() {
		if (!impl) {
			impl = std::make_unique<players_manager>();
		}
		return *impl;
	}

public:
	static std::uint32_t create_human_player(const std::string& player_name = "") {
		auto& instance = get_instance();
		instance.players.emplace_back(std::make_pair(player_name, false));
		return instance.players.size() - 1;
	}

	static std::uint32_t create_ai_player(const std::string& player_name) {
		auto& instance = get_instance();
		instance.players.emplace_back(std::make_pair(player_name, true));
		return instance.players.size() - 1;
	}

	static void add_entity_for_player(std::uint32_t player_id, std::uint32_t entity_id) {
		get_instance().entity_id_to_player_id[entity_id] = player_id;
	}

	static void add_neutral_entity(std::uint32_t entity_id) {
		get_instance().entity_id_to_player_id[entity_id] = neutral_id;
	}

	static bool player_entity(std::uint32_t player_id, std::uint32_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] == player_id;
	}
	static bool active_player_entity(std::uint32_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] == get_instance().active_player_id;
	}

	static bool enemy_entity(std::uint32_t player_id, std::uint32_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] != player_id
			   && get_instance().entity_id_to_player_id[entity_id] != neutral_id;
	}

	static bool neutral_entity(std::uint32_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] == neutral_id;
	}


	static std::string player_name(std::uint32_t player_id) {
		return get_instance().players[player_id].first;
	}

	static std::uint32_t player_for_entity(std::uint32_t entity_id) {
		auto it = get_instance().entity_id_to_player_id.find(entity_id);
		if (it != std::end(get_instance().entity_id_to_player_id)) {
			return it->second;
		} else {
			return no_player;
		}
	}

	static std::uint32_t get_active_player_id() {
		return get_instance().active_player_id;
	}

	static std::uint32_t next_player() {
		auto& instance = get_instance();
		auto next_player_id = ++instance.active_player_id % instance.players.size();
		instance.active_player_id = next_player_id;
		return next_player_id;
	}

	static bool is_active_player_ai() {
		auto& instance = get_instance();
		return instance.players[instance.active_player_id].second;
	}

	static const std::uint32_t neutral_id = std::numeric_limits<std::uint32_t>::max();
	static const std::uint32_t no_player = std::numeric_limits<std::uint32_t>::max();

private:
	std::vector<std::pair<std::string, bool>> players;
	std::unordered_map<std::uint32_t, std::uint32_t> entity_id_to_player_id;
	std::uint32_t active_player_id{0};
};

namespace players_funcs
{

void player_entities_indexes(std::uint32_t player_id, std::vector<std::uint32_t>& indexes);
void enemy_entities_indexes(std::uint32_t player_id, std::vector<std::uint32_t>& indexes);

bool player_entity(std::uint32_t entity_index);
bool enemy_entity(std::uint32_t entity_index);
bool neutral_entity(std::uint32_t entity_index);
std::uint32_t active_player_first_entity_index();

}

#endif