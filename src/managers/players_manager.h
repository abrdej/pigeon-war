#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class entity;

class players_manager {
public:
	std::uint32_t create_human_player(const std::string& player_name = "") {
		players.emplace_back(std::make_pair(player_name, false));
		return players.size() - 1;
	}

	std::uint32_t create_ai_player(const std::string& player_name) {
		players.emplace_back(std::make_pair(player_name, true));
		return players.size() - 1;
	}

	void add_entity_for_player(std::uint32_t player_id, std::uint32_t entity_id) {
		entity_id_to_player_id[entity_id] = player_id;
	}

	void add_neutral_entity(std::uint32_t entity_id) {
		entity_id_to_player_id[entity_id] = neutral_id;
	}

	void add_destructive_surroundings(std::uint32_t entity_id) {
		entity_id_to_player_id[entity_id] = destructive_surroundings_id;
	}

	bool player_entity(std::uint32_t player_id, std::uint32_t entity_id) {
		return entity_id_to_player_id[entity_id] == player_id;
	}
	bool active_player_entity(std::uint32_t entity_id) {
		return entity_id_to_player_id[entity_id] == active_player_id;
	}

	bool enemy_entity(std::uint32_t player_id, std::uint32_t entity_id) {
		return entity_id_to_player_id[entity_id] != player_id
			   && entity_id_to_player_id[entity_id] != neutral_id;
	}

	bool neutral_entity(std::uint32_t entity_id) {
		return entity_id_to_player_id[entity_id] == neutral_id;
	}


	std::string player_name(std::uint32_t player_id) {
		return players[player_id].first;
	}

	std::uint32_t player_for_entity(std::uint32_t entity_id) {
		auto it = entity_id_to_player_id.find(entity_id);
		if (it != std::end(entity_id_to_player_id)) {
			return it->second;
		} else {
			return no_player;
		}
	}

	std::uint32_t get_active_player_id() {
		return active_player_id;
	}

	std::uint32_t next_player() {
		auto next_player_id = ++active_player_id % players.size();
		active_player_id = next_player_id;
		return next_player_id;
	}

	bool is_active_player_ai() {
		return players[active_player_id].second;
	}

	const std::uint32_t neutral_id = std::numeric_limits<std::uint32_t>::max();
	const std::uint32_t destructive_surroundings_id = std::numeric_limits<std::uint32_t>::max() - 1;
	const std::uint32_t no_player = std::numeric_limits<std::uint32_t>::max();

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