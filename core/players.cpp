#include "players.h"

std::vector<std::pair<players::player_id_type, bool>> players::players_;
size_t players::active_player_ = 0;
std::unordered_map<size_t, players::player_id_type> players::relation_map_;
const players::player_id_type players::neutral_id;


void players::create_human_player(const player_id_type& name)
{
	players_.push_back(std::make_pair(name, false));
}

void players::create_ai_player(const player_id_type& name)
{
	players_.push_back(std::make_pair(name, true));
}

void players::add_entity_for_player(const player_id_type& name, size_t entity_id)
{
	auto it = relation_map_.insert(std::make_pair(entity_id, name));
	it.first->second = name;
}

void players::add_neutral_entity(size_t entity_id)
{
	auto it = relation_map_.insert(std::make_pair(entity_id, neutral_id));
	it.first->second = neutral_id;
}

bool players::player_entity(player_id_type player_id, size_t entity_id)
{
	return relation_map_[entity_id] == player_id;
}

bool players::enemy_entity(player_id_type player_id, size_t entity_id)
{
	return relation_map_[entity_id] != player_id && relation_map_[entity_id] != neutral_id;
}

const players::player_id_type& players::active_player_name()
{
	return players_[active_player_].first;
}

bool players::active_player_ai()
{
	return players_[active_player_].second;
}

void players::next_player()
{
	active_player_ = (++active_player_) % players_.size();
}

namespace players_funcs
{
	void player_entities_indexies(const players::player_id_type& player_name, std::vector<size_t>& indexies)
	{
		indexies.clear();
		board::call_worker([&player_name, &indexies](size_t entity_id,
			size_t col, size_t row)
		{
			if (entity_id != -1 && players::player_entity(player_name, entity_id))
				indexies.push_back(board::to_index(col, row));
		});
	}

	void enemy_entities_indexies(const players::player_id_type& player_name, std::vector<size_t>& indexies)
	{
		indexies.clear();
		board::call_worker([&player_name, &indexies](size_t entity_id,
			size_t col, size_t row)
		{
			if (entity_id != -1 && players::enemy_entity(player_name, entity_id))
				indexies.push_back(board::to_index(col, row));
		});
	}
}