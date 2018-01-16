#include "players_manager.h"
#include "managers/entity_manager.h"


std::unique_ptr<players_manager> players_manager::impl;

//std::vector<std::pair<players::player_id_type, bool>> players::players_;
//std::uint64_t players::active_player_ = 0;
//std::unordered_map<std::uint64_t, players::player_id_type> players::relation_map_;
//const players::player_id_type players::neutral_id;
//
//
//void players::create_human_player(const player_id_type& name)
//{
//	players_.emplace_back(std::make_pair(name, false));
//}
//
//void players::create_ai_player(const player_id_type& name)
//{
//	players_.emplace_back(std::make_pair(name, true));
//}
//
//void players::add_entity_for_player(const player_id_type& name, std::uint64_t entity_id)
//{
//	auto it = relation_map_.insert(std::make_pair(entity_id, name));
//	it.first->second = name;
//}
//
//void players::add_neutral_entity(std::uint64_t entity_id)
//{
//	auto it = relation_map_.insert(std::make_pair(entity_id, neutral_id));
//	it.first->second = neutral_id;
//}
//
//bool players::player_entity(player_id_type player_id, std::uint64_t entity_id)
//{
//	return relation_map_[entity_id] == player_id;
//}
//
//bool players::enemy_entity(player_id_type player_id, std::uint64_t entity_id)
//{
//	return relation_map_[entity_id] != player_id && relation_map_[entity_id] != neutral_id;
//}
//
//bool players::neutral_entity(std::uint64_t entity_id) {
//	return relation_map_[entity_id] == neutral_id;
//}
//
//const players::player_id_type& players::active_player_name()
//{
//	return players_[active_player_].first;
//}
//
//bool players::active_player_ai()
//{
//	return players_[active_player_].second;
//}
//
//std::uint64_t players::active_player_index() {
//	return active_player_;
//}
//
//void players::next_player()
//{
//	active_player_ = (++active_player_) % players_.size();
//}
//
//players::player_id_type players::player_for_entity(std::uint64_t entity_id) {
//	return relation_map_[entity_id];
//}

void players_funcs::player_entities_indexes(std::uint64_t player_id, std::vector<std::uint64_t>& indexes)
{
	indexes.clear();
	board::for_each([&player_id, &indexes](std::uint64_t entity_id, std::uint64_t col, std::uint64_t row) {
		if (entity_id != -1 && players_manager::player_entity(player_id, entity_id))
			indexes.push_back(board::to_index(col, row));
	});
}

void players_funcs::enemy_entities_indexes(std::uint64_t player_id, std::vector<std::uint64_t>& indexes)
{
	indexes.clear();
	board::for_each([player_id, &indexes](std::uint64_t entity_id, std::uint64_t col, std::uint64_t row) {
		if (entity_id != -1 && players_manager::enemy_entity(player_id, entity_id))
			indexes.push_back(board::to_index(col, row));
	});
}

bool players_funcs::player_entity(std::uint64_t entity_index)
{
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players_manager::player_entity(players_manager::get_active_player_id(), entity_id);
	return false;
}

bool players_funcs::enemy_entity(std::uint64_t entity_index)
{
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players_manager::enemy_entity(players_manager::get_active_player_id(), entity_id);
	return false;
}

bool players_funcs::neutral_entity(std::uint64_t entity_index) {
	auto entity_id = board::at(entity_index);
	if (entity_id != -1)
		return players_manager::neutral_entity(entity_id);
	return false;
}

std::uint64_t players_funcs::active_player_first_entity_index()
{
	std::vector<std::uint64_t> indexes;
	players_funcs::player_entities_indexes(players_manager::get_active_player_id(), indexes);
	if (!indexes.empty()) {
		return indexes[0];
	}
	return std::numeric_limits<std::uint64_t>::max();
}