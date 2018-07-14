#include <iostream>
#include <core/board.h>
#include <core/states_controller.h>
#include <abilities/ability.h>
#include <abilities/abilities.h>
#include <managers/players_manager.h>
#include <chrono>
#include <thread>
#include <scenarios/skirmish.h>
#include <components/applied_effects.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include <components/power_field.h>
#include <scenarios/wolves_dinner.h>
#include <scenarios/saurian_web_scenario.h>
#include <scenarios/battle_with_a_golem_scenario.h>
#include "core/game.h"
#include "core/game_state.h"
#include "server/server.h"
#include "sender.h"
#include "external/json.hpp"
#include "messages/messages.h"
#include "components/damage_taker.h"

auto get_names() {
	std::unordered_map<std::uint32_t, std::string> returned_map;
	game::get<entity_manager>().for_all([&returned_map](base_entity entity) {
		returned_map.insert(std::make_pair(entity.entity_id, entity.name));
	});
	return std::move(returned_map);
}

game_state get_game_state(game& g) {

	game_state state;
	state.healths = get_healths();
	state.board.set_size(game::get<board>().cols_n, game::get<board>().rows_n);

	for (std::uint32_t i = 0; i < game::get<board>().fields_.size(); ++i) {
		for (auto&& elem : game::get<board>().fields_[i]) {
			state.board.fields_[i].push_back(elem);
		}
	}

	state.entities_names = get_names();
	state.entities_additional_effects = get_effects();

	return std::move(state);
}

local_state get_local_state(game& g) {

	local_state state;

	for (auto&& idx : states::state_controller::possible_movements_)
		state.possible_movements.push_back(idx);

	state.actual_target_type = states::state_controller::actual_targeting_type_;

	state.button_bitmaps.fill("");

	auto entity_id = game::get<board>().at(states::state_controller::selected_index_);
	auto entity = game::get<entity_manager>().get(entity_id);

	if (entity_id != game::get<board>().empty_id) {

		if (entity.contain<abilities>()) {
			auto abilities_ptr = entity.get<abilities>();
			for (std::int32_t i = 0; i < 5; ++i) {
				auto ability = abilities_ptr->at(i);
				if (ability) {
					state.button_bitmaps[i] = ability->get_bitmap_key();
				}
			}
		}
	}

	state.entity_name = entity.name;
	state.selected_index = states::state_controller::selected_index_;

	for (auto&& move : states::state_controller::possible_movements_) {
		if (states::state_controller::valid_target(move)) {
			state.valid_movements.insert(move);
		}
	}

	return std::move(state);
}

auto get_entities() {
    std::unordered_map<std::uint32_t, std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>> returned_map;
    game::get<entity_manager>().for_all([&returned_map](base_entity entity) {
        returned_map.insert(std::make_pair(entity.entity_id,
										   std::make_tuple(entity.name,
                                                           entity.get<health_field>()->health,
                                                           entity.contain<power_filed>() ? entity.get<power_filed>()->power
                                                                                         : std::numeric_limits<std::int32_t>::max(),
                                                           game::get<board>().index_for(entity.entity_id))));
    });
    return std::move(returned_map);
}

int main(int argc, char** argv) {

	std::int32_t port = 5555;
	std::string map_name = "battlefield";
	std::pair<std::uint32_t, std::uint32_t> map_size;

	if (argc > 1) {
		port = std::atoi(argv[1]);
	}
	if (argc == 3) {
		map_name = std::string(argv[2]);
	}

	game g;
//    map_name = create_skirmish(g, map_name, map_size);
	game::get<board>().set_size(15, 10);
//	create_wolves_dinner(g);
//	create_saurian_web(g);
	create_battle_with_a_golem_scenario();
	map_name = "Wolves dinner";

	tcp_server pigeon_war_server(port);

	sender::set_sender([&pigeon_war_server](std::string message) {
		pigeon_war_server.send_notification(message);
	});

	pigeon_war_server.set_initial_message([&](std::uint32_t client_id) {
		pigeon_war_server.send_notification_to(client_id, make_map_size_message(map_size));
		pigeon_war_server.send_notification_to(client_id, make_client_id_message(client_id));
        pigeon_war_server.send_notification_to(client_id, make_map_name_message(map_name));
		pigeon_war_server.send_notification_to(client_id, make_entities_pack_message(get_entities()));
	});

    using json_data_type = nlohmann::json;

	pigeon_war_server.bind("on_board", [&](json_data_type& data) {

		std::cout << "on board\n";

		std::int32_t client_id = data["client_id"];
		std::uint32_t x = data["col"];
		std::uint32_t y = data["row"];

        bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {
			g.on_board(x, y);
			pigeon_war_server.send_notification(make_local_state_message(get_local_state(g)));
			pigeon_war_server.send_notification(make_game_state_message(get_game_state(g)));
		}
	});

	pigeon_war_server.bind("on_button", [&](json_data_type& data) {

		std::cout << "on button\n";

		std::int32_t client_id = data["client_id"];
		std::uint32_t button = data["button"];

		const bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

			std::cout << "client_id: " << client_id << " single_client:" << single_client << "\n";

			g.on_button(button);

			if (button == 5) {
				auto active_player = game::get<players_manager>().get_active_player_id();
				pigeon_war_server.send_notification(make_end_turn_message(active_player));
			}

			pigeon_war_server.send_notification(make_local_state_message(get_local_state(g)));
			pigeon_war_server.send_notification(make_game_state_message(get_game_state(g)));
		}
	});

	pigeon_war_server.bind("get_button_description", [&](json_data_type& data) {

		std::int32_t client_id = data["client_id"];
		std::uint32_t button = data["button"];

		std::string description;

		const bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

			description = g.get_button_description(states::state_controller::selected_index_, button);
			pigeon_war_server.send_notification_to(client_id, make_description_message(description));
		}
	});

	pigeon_war_server.run();
    pigeon_war_server.wait();

	return 0;
}