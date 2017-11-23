#include "players.h"
#include "managers/entity_manager.h"

std::vector<std::pair<players::player_id_type, bool>> players::players_;
size_t players::active_player_ = 0;
std::unordered_map<std::size_t, players::player_id_type> players::relation_map_;
const players::player_id_type players::neutral_id;


void players::create_human_player(const player_id_type& name)
{
	players_.emplace_back(std::make_pair(name, false));
}

void players::create_ai_player(const player_id_type& name)
{
	players_.emplace_back(std::make_pair(name, true));
}

void players::add_entity_for_player(const player_id_type& name, size_t entity_id)
{
	auto it = relation_map_.insert(std::make_pair(entity_id, name));
	it.first->second = name;
}

void players::add_neutral_entity(std::size_t entity_id)
{
	auto it = relation_map_.insert(std::make_pair(entity_id, neutral_id));
	it.first->second = neutral_id;
}

bool players::player_entity(player_id_type player_id, std::size_t entity_id)
{
	return relation_map_[entity_id] == player_id;
}

bool players::enemy_entity(player_id_type player_id, std::size_t entity_id)
{
	return relation_map_[entity_id] != player_id && relation_map_[entity_id] != neutral_id;
}

bool players::neutral_entity(size_t entity_id) {
	return relation_map_[entity_id] == neutral_id;
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

void player_entities_indexes(const players::player_id_type& player_name, std::vector<std::size_t>& indexes)
{
	indexes.clear();
	board::for_each([&player_name, &indexes](std::size_t entity_id, std::size_t col, std::size_t row) {
		if (entity_id != -1 && players::player_entity(player_name, entity_id))
			indexes.push_back(board::to_index(col, row));
	});
}

void enemy_entities_indexes(const players::player_id_type& player_name, std::vector<std::size_t>& indexes)
{
	indexes.clear();
	board::for_each([&player_name, &indexes](std::size_t entity_id, std::size_t col, std::size_t row) {
		if (entity_id != -1 && players::enemy_entity(player_name, entity_id))
			indexes.push_back(board::to_index(col, row));
	});
}

bool player_entity(std::size_t entity_index)
{
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players::player_entity(players::active_player_name(), entity_id);
	return false;
}

bool enemy_entity(std::size_t entity_index)
{
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players::enemy_entity(players::active_player_name(), entity_id);
	return false;
}

bool neutral_entity(std::size_t entity_index) {
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players::neutral_entity(entity_id);
	return false;
}

std::size_t active_player_first_entity_index()
{
	std::vector<std::size_t> indexies;
	players_funcs::player_entities_indexes(players::active_player_name(), indexies);
	if (!indexies.empty()) {
		return indexies[0];
	}
	return std::numeric_limits<std::size_t>::max();
}

}