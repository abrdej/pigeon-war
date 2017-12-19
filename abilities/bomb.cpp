#include "bomb.h"
#include "damage_dealers.h"
#include <core/states.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <animation/animation.h>
#include <unordered_map>

bomb_detonation::bomb_detonation(std::size_t bomb_id) : bomb_id(bomb_id) {
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

void bomb_detonation::prepare(size_t for_index) {
//	states::state_controller::actual_state_ = states::states_types::wait_for_action;
//	states::state_controller::possible_movements_.push_back(for_index);
//	states::state_controller::actual_targeting_type_ = states::target_types::caster;
//	states::state_controller::wait_for_action([this](size_t index)
//											  {
//												  return use(index);
//											  });
}

void bomb_detonation::use(size_t for_index) {

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(for_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

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

void bomb_detonation(std::size_t bomb_id, int damage) {

	auto index = board::index_for(bomb_id);

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

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

void bomb::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void bomb::use(size_t index) {

	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	animation::player<animation::move>::launch(animation::move(used_from_index, index, bitmap_key::bomb));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index), entity_id));

	std::size_t next_index = index;

	std::unordered_set<std::size_t> visited_indexes;
	visited_indexes.insert(next_index);

	while (next_index != std::numeric_limits<std::size_t>::max()) {

		auto from_index = next_index;

		next_index = find_min_health_jump(next_index, visited_indexes);

		if (next_index == std::numeric_limits<std::size_t>::max()) {
			break;
		}

		animation::player<animation::move>::launch(animation::move(from_index, next_index, bitmap_key::bomb));
		animation::base_player::play();
		animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(next_index, std::chrono::milliseconds(150), "bum.png"));
		animation::base_player::play();

		damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(next_index), entity_id));

		visited_indexes.insert(next_index);
	}

	used = true;
}

std::size_t bomb::find_min_health_jump(std::size_t from_index, std::unordered_set<std::size_t>& visited_indexes) {
	std::vector<std::size_t> neighbors;
	board_helper::neighboring_fields(from_index, neighbors, false);

	std::size_t min_health_index = std::numeric_limits<std::size_t>::max();
	int min_health = std::numeric_limits<int>::max();

	for (std::size_t i  = 0; i < neighbors.size(); ++i) {
		if (!board::empty(neighbors[i]) && visited_indexes.find(neighbors[i]) == std::end(visited_indexes)) {

			auto neighbor_id = board::at(neighbors[i]);
			auto health_pack = healths_manager::component_for(neighbor_id);

			if (health_pack.health < min_health) {
				min_health_index = i;
				min_health = health_pack.health;
			}
		}
	}
	if (min_health_index != std::numeric_limits<std::size_t>::max())
		return neighbors[min_health_index];
	else
		return std::numeric_limits<std::size_t>::max();
}