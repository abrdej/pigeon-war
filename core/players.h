#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "core/board.h"

class entity;

class players final
{
public:
	using player_id_type = std::string;
	static void create_human_player(const player_id_type& name);
	static void create_ai_player(const player_id_type& name);
	static void add_entity_for_player(const player_id_type& name, size_t entity_id);
	static void add_neutral_entity(size_t entity_id);
	static bool player_entity(player_id_type player_id, size_t entity_id);
	static bool enemy_entity(player_id_type player_id, size_t entity_id);
	static const player_id_type& active_player_name();
	static bool active_player_ai();
	static void next_player();

private:
	static std::vector<std::pair<player_id_type, bool>> players_;
	static size_t active_player_;
	static std::unordered_map<size_t, player_id_type> relation_map_;
	static const player_id_type neutral_id;
};

namespace players_funcs
{
	void player_entities_indexies(const players::player_id_type& player_name, std::vector<size_t>& indexies);
	void enemy_entities_indexies(const players::player_id_type& player_name, std::vector<size_t>& indexies);
}

#endif