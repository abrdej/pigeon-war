#include "wolf_herd.h"
#include <core/states_controller.h>
#include <entities/wolf.h>
#include <managers/entity_manager.h>
#include <random>

void wolf_herd::prepare(size_t for_index) {

	states::state_controller::actual_state_ = states::states_types::wait_for_action;
	states::state_controller::possible_movements_.push_back(for_index);
	states::state_controller::actual_targeting_type_ = states::target_types::caster;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void wolf_herd::use(size_t index_on) {

	if (used)
		return;

	used = true;

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(index_on, neightbords, true);

	std::random_device rd;
	std::default_random_engine dre(rd());

	auto num_of_wolves = std::min<int>(neightbords.size(), max_number_of_wolf);

	for (int n = 0; n < num_of_wolves; ++n) {

		std::uniform_int_distribution<int> uniform_dist(0, neightbords.size() - 1);

		int place_idx = uniform_dist(dre);

		auto wolf_id = entity_manager::create<wolf>();
		auto player_name = players::active_player_name();
		players::add_entity_for_player(player_name, wolf_id);
		board::insert(neightbords[place_idx], wolf_id);

		neightbords.erase(neightbords.begin() + place_idx);
	}
}
