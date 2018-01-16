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
	static std::uint64_t create_human_player(const std::string& player_name = "") {
		auto& instance = get_instance();
		instance.players.emplace_back(std::make_pair(player_name, false));
		return instance.players.size() - 1;
	}

	static std::uint64_t create_ai_player(const std::string& player_name) {
		auto& instance = get_instance();
		instance.players.emplace_back(std::make_pair(player_name, true));
		return instance.players.size() - 1;
	}

	static void add_entity_for_player(std::uint64_t player_id, std::uint64_t entity_id) {
		get_instance().entity_id_to_player_id[entity_id] = player_id;
	}

	static void add_neutral_entity(std::uint64_t entity_id) {
		get_instance().entity_id_to_player_id[entity_id] = neutral_id;
	}

	static bool player_entity(std::uint64_t player_id, std::uint64_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] == player_id;
	}

	static bool enemy_entity(std::uint64_t player_id, std::uint64_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] != player_id
			   && get_instance().entity_id_to_player_id[entity_id] != neutral_id;
	}

	static bool neutral_entity(std::uint64_t entity_id) {
		return get_instance().entity_id_to_player_id[entity_id] == neutral_id;
	}


	static std::string player_name(std::uint64_t player_id) {
		return get_instance().players[player_id].first;
	}

	static std::uint64_t player_for_entity(std::uint64_t entity_id) {
		return get_instance().entity_id_to_player_id.at(entity_id);
	}

	static std::uint64_t get_active_player_id() {
		return get_instance().active_player_id;
	}

	static std::uint64_t next_player() {
		auto& instance = get_instance();
		auto next_player_id = ++instance.active_player_id % instance.players.size();
		instance.active_player_id = next_player_id;
		return next_player_id;
	}

	static bool is_active_player_ai() {
		auto& instance = get_instance();
		return instance.players[instance.active_player_id].second;
	}

private:
	static const std::uint64_t neutral_id = std::numeric_limits<std::uint64_t>::max();
	std::vector<std::pair<std::string, bool>> players;
	std::unordered_map<std::uint64_t, std::uint64_t> entity_id_to_player_id;
	std::uint64_t active_player_id{0};
};

namespace players_funcs
{

void player_entities_indexes(std::uint64_t player_id, std::vector<std::uint64_t>& indexes);
void enemy_entities_indexes(std::uint64_t player_id, std::vector<std::uint64_t>& indexes);

bool player_entity(std::uint64_t entity_index);
bool enemy_entity(std::uint64_t entity_index);
bool neutral_entity(std::uint64_t entity_index);
std::uint64_t active_player_first_entity_index();

}

#endif