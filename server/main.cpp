#include <iostream>
#include <core/board.h>
#include <core/states_controller.h>
#include <abilities/ability.h>
#include <core/animations_queue.h>
#include <managers/players_manager.h>
#include <chrono>
#include <thread>
#include <common/turn_status.h>
#include <SFML/Network.hpp>
#include <scenarios/scenarios.h>
#include <components/additions.h>
#include <managers/entity_manager.h>
#include "core/game.h"
#include "common/game_state.h"
#include "server.h"
#include "common/packet_helper.h"
#include "sender.h"
#include "cbor/cbor.h"
#include "json.hpp"
#include "common/messages/messages.h"

game_state get_game_state(game& g) {

	game_state state;
	state.healths = get_healths();

	for (std::uint32_t i = 0; i < board::fields_.size(); ++i) {
		for (auto&& elem : board::fields_[i]) {
			state.board.fields_[i].push_back(elem);
		}
	}

	state.entities_names = get_names();
	state.entities_additional_effects = get_additions();

	return std::move(state);
}

local_state get_local_state(game& g) {

	local_state state;

	for (auto&& idx : states::state_controller::possible_movements_)
		state.possible_movements.push_back(idx);

	state.actual_target_type = states::state_controller::actual_targeting_type_;

	state.button_bitmaps.fill(bitmap_key::none);

	auto entity_id = board::at(states::state_controller::selected_index_);
	auto entity = entity_manager::get(entity_id);

	if (entity_id != board::empty_id) {

		state.button_bitmaps[0] = entity.get<bitmap_field>()->bmt_key;

		if (entity.contain<abilities>()) {
			auto abilities_ptr = entity.get<abilities>();
			for (std::int32_t i = 1; i < 6; ++i) {
				auto ability = abilities_ptr->at(i - 1);
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

int main(int argc, char** argv) {

	int port = 5555;

	if (argc > 1) {
		port = std::atoi(argv[1]);
	}

	game g;

	create_scenario(g,  "saurions_web");

	server binder(port);

	sender::set_sender([&binder](sf::Packet packet) {
		binder.send_notification(packet);
	});

	binder.bind(message_types::on_board, [&](sf::Packet& packet) {

		std::int32_t client_id;
		std::uint32_t x;
		std::uint32_t y;

		packet >> client_id;
		packet >> x;
		packet >> y;

        bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {
			g.on_board(x, y);

//			binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));
			binder.send_notification(make_packet(message_types::local_state, get_local_state(g)));
			binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));

		}
	});

	binder.bind(message_types::on_button, [&](sf::Packet& packet) {

		std::int32_t client_id;
		std::uint32_t n;

		packet >> client_id;
		packet >> n;

		std::cout << "N1: " << n << "\n";

		const bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {

			std::cout << "client_id: " << client_id << " single_client:" << single_client << "\n";

			g.on_button(n);

			std::cout << "N2: " << n << "\n";

			if (n == 5) {

				auto active_player = players_manager::get_active_player_id();

				sf::Packet result_packet;
				result_packet << message_types::end_turn << active_player;

				binder.send_notification(result_packet);
			}

//			binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));

			binder.send_notification(make_packet(message_types::local_state, get_local_state(g)));
			binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));
		}
	});

	binder.bind(message_types::get_button_description, [&](sf::Packet& packet) {

		std::int32_t client_id;
		std::uint32_t n;

		packet >> client_id;
		packet >> n;

		std::string description;

		const bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {

			description = g.get_button_description(states::state_controller::selected_index_, n);

			binder.send_notification_to(client_id, make_packet(message_types::description, description));

		}
	});

	binder.start();

	binder.working_thread.join();

	return 0;
}