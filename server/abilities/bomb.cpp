#include "bomb.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <unordered_map>

bomb_detonation::bomb_detonation(sf::Uint64 bomb_id) : bomb_id(bomb_id) {
//	onEveryRound([this]() {
//
//		if (waited) {
//			auto index = board::index_for(this->bomb_id);
//			use(index);
//		}
//
//		waited = true;
//	});
}

void bomb_detonation::look_for_bombs() {

}

void bomb_detonation::prepare(sf::Uint64 for_index) {
//	states::state_controller::actual_state_ = states::states_types::wait_for_action;
//	states::state_controller::possible_movements_.push_back(for_index);
//	states::state_controller::actual_targeting_type_ = states::target_types::caster;
//	states::state_controller::wait_for_action([this](sf::Uint64 index)
//											  {
//												  return use(index);
//											  });
}

void bomb_detonation::use(sf::Uint64 for_index) {

	std::vector<sf::Uint64> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

	animations_queue::push_animation(animation_types::flash_bitmap, for_index, 150, 0, bitmap_key::bum);

	auto final_damage = damage;

	for (auto& index : neightbords)
	{
		auto id = board::at(index);
		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
			return *ptr == id;
		});
		if (it != buffer->end()) {
			final_damage += 5;
		}
	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}
	}

	entity_manager::destroy(bomb_id);
}

void bomb_detonation(sf::Uint64 bomb_id, sf::Int32 damage) {

	auto index = board::index_for(bomb_id);

	std::vector<sf::Uint64> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

	animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::bum);

//	auto final_damage = damage;
//
//	for (auto& index : neightbords)
//	{
//		auto id = board::at(index);
//		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
//			return *ptr == id;
//		});
//		if (it != buffer->end()) {
//			final_damage += 5;
//		}
//	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}

	}

	entity_manager::destroy(bomb_id);
}

bomb::bomb() {

	onEveryRound([this]() {
		used = false;
	});
}

void bomb::prepare(sf::Uint64 for_index) {

	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](sf::Uint64 index)
											  {
												  return use(index);
											  });
}

void bomb::use(sf::Uint64 index) {

	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	animations_queue::push_animation(animation_types::move, used_from_index, index, -1, bitmap_key::bomb);
	animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::bum);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index), entity_id));

	sf::Uint64 next_index = index;

	std::unordered_set<sf::Uint64> visited_indexes;
	visited_indexes.insert(next_index);

	while (next_index != std::numeric_limits<sf::Uint64>::max()) {

		auto from_index = next_index;

		next_index = find_min_health_jump(next_index, visited_indexes);

		if (next_index == std::numeric_limits<sf::Uint64>::max()) {
			break;
		}

		animations_queue::push_animation(animation_types::move, from_index, next_index, -1, bitmap_key::bomb);
		animations_queue::push_animation(animation_types::flash_bitmap, next_index, 150, 0, bitmap_key::bum);

		damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(next_index), entity_id));

		visited_indexes.insert(next_index);
	}

	used = true;
}

sf::Uint64 bomb::find_min_health_jump(sf::Uint64 from_index, std::unordered_set<sf::Uint64>& visited_indexes) {
	std::vector<sf::Uint64> neighbors;
	board_helper::neighboring_fields(from_index, neighbors, false);

	sf::Uint64 min_health_index = std::numeric_limits<sf::Uint64>::max();
	sf::Int32 min_health = std::numeric_limits<sf::Int32>::max();

	for (sf::Uint64 i  = 0; i < neighbors.size(); ++i) {
		if (!board::empty(neighbors[i]) && visited_indexes.find(neighbors[i]) == std::end(visited_indexes)) {

			auto neighbor_id = board::at(neighbors[i]);
			auto health_pack = healths_manager::component_for(neighbor_id);

			if (health_pack.health < min_health) {
				min_health_index = i;
				min_health = health_pack.health;
			}
		}
	}
	if (min_health_index != std::numeric_limits<sf::Uint64>::max())
		return neighbors[min_health_index];
	else
		return std::numeric_limits<sf::Uint64>::max();
}