#include <iostream>
#include <chrono>
#include <thread>

#include <external/json.hpp>

#include <abilities/abilities.h>

#include <components/applied_effects.h>
#include <components/damage_taker.h>

#include <core/game_controller.h>
#include <core/get_button_description.h>
#include <core/get_effect_description.h>
#include <core/get_game_state.h>

#include <managers/get_entities.h>
#include <managers/get_entity_names.h>

#include <scenarios/battle_with_a_golem_scenario.h>
#include <scenarios/dark_forest.h>
#include <scenarios/saurian_web_scenario.h>
#include <scenarios/skirmish.h>
#include <scenarios/total_destruction.h>
#include <scenarios/wolves_dinner.h>

#include <server/server.h>

int main(int argc, char** argv) {

    // main server will start this.
    // same initialization will be passed by config file
    // maybe in json
    // map name, entities to select, players token, etc.

	// parse some initial arguments
	// create game
	// set up server
	// run server

	std::int32_t port = 8080;
//	std::string map_name = "battlefield";
	std::string map_name = "winter_forest";
	std::string scenario = "skirmish";
	std::pair<std::uint32_t, std::uint32_t> map_size;

	if (argc > 1) {
		port = std::atoi(argv[1]);
	}
	if (argc == 3) {
//		map_name = std::string(argv[2]);
        scenario = std::string(argv[2]);
	}

    static std::unordered_map<std::string, std::function<void()>>
            scenario_loader = {
            {"skirmish", [&map_name, &map_size]() {
                map_name = create_skirmish(map_name, map_size);
            }},
            {"saurian_web", []() {
                create_saurian_web();
            }},
            {"wolves_dinner", []() {
                create_wolves_dinner();
            }},
			{"dark_forest", []() {
				scenario::create_dark_forest();
			}}
    };
    scenario_loader.at(scenario)();

	// create game
//    map_name = create_skirmish(map_name, map_size);
	//create_wolves_dinner();
//	create_saurian_web();
//	scenarios::create_total_destruction();
//    scenarios::create_battle_with_a_golem_scenario();
//	map_name = "Battle with a golem";

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
			game_control().on_board(x, y);
			pigeon_war_server.send_notification(make_local_game_state_message(get_local_game_state()));
			pigeon_war_server.send_notification(make_global_game_state_message(get_global_game_state()));
		}
	});

	pigeon_war_server.bind("on_button", [&](json_data_type& data) {

		std::cout << "on button\n";

		std::int32_t client_id = data["client_id"];
		std::uint32_t button = data["button"];

		const bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

			std::cout << "client_id: " << client_id << " single_client:" << single_client << "\n";

			game_control().on_button(button);

			if (button == 5) {
				auto active_player = game::get<players_manager>().get_active_player_id();
				pigeon_war_server.send_notification(make_end_turn_message(active_player));
			}

			pigeon_war_server.send_notification(make_local_game_state_message(get_local_game_state()));
			pigeon_war_server.send_notification(make_global_game_state_message(get_global_game_state()));
		}
	});

	pigeon_war_server.bind("get_button_description", [&](json_data_type& data) {

		std::int32_t client_id = data["client_id"];
		std::uint32_t button = data["button"];

		std::string description;

		const bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

			description = get_button_description(game_control().selected_index_, button);
			pigeon_war_server.send_notification_to(client_id, make_description_message(description));
		}
	});

	pigeon_war_server.bind("get_effect_description", [&](json_data_type& data) {

		std::int32_t client_id = data["client_id"];
		std::string effect = data["effect"];

		std::string description;

		const bool single_client = pigeon_war_server.is_single_client();

		if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {
			description = get_effect_description(effect);
			pigeon_war_server.send_notification_to(client_id, make_effect_description_message(description));
		}
	});

	pigeon_war_server.run();
    pigeon_war_server.wait();

	return 0;
}