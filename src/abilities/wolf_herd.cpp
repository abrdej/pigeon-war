#include "wolf_herd.h"
#include "core/states_controller.h"
#include "entities/wolf.h"
#include "managers/entity_manager.h"
#include "managers/players_manager.h"
#include <random>

void wolf_herd::use(std::uint32_t index_on) {

	if (used)
		return;

	used = true;

	std::vector<std::uint32_t> neighbors;
	board_helper::neighboring_fields(index_on, neighbors, true);

	std::random_device rd;
	std::default_random_engine dre(rd());

	auto num_of_wolves = std::min<std::int32_t>(neighbors.size(), max_number_of_wolf);

	for (std::int32_t n = 0; n < num_of_wolves; ++n) {

		std::uniform_int_distribution<std::int32_t> uniform_dist(0, neighbors.size() - 1);

		std::int32_t place_idx = uniform_dist(dre);

		auto wolf_id = game::get<entity_manager>().create<wolf>();
		auto player_name = game::get<players_manager>().get_active_player_id();
		game::get<players_manager>().add_entity_for_player(player_name, wolf_id);
		game::get<board>().insert(neighbors[place_idx], wolf_id);

		neighbors.erase(neighbors.begin() + place_idx);
	}
}
