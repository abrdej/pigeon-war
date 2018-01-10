#include <iostream>
#include <core/board.h>
#include <core/states_controller.h>
#include <managers/abilities_manager.h>
#include <abilities/ability.h>
#include <core/animations_queue.h>
#include <managers/players_manager.h>
#include <chrono>
#include <thread>
#include <common/turn_status.h>
#include <SFML/Network.hpp>
#include "core/game.h"
#include "common/game_state.h"
#include "managers/bitmap_field_manager.h"
#include "managers/health_manager.h"
#include "managers/names_manager.h"
#include "server.h"
#include "common/packet_helper.h"
#include "sender.h"

game_state get_game_state(game& g) {

	game_state state;
	state.healths = healths_manager::get_map();
	state.board.fields_ = board::fields_;
	state.entities_bitmaps = bitmap_field_manager::get_map();

	return std::move(state);
}

local_state get_local_state(game& g) {

	local_state state;

	state.possible_movements = states::state_controller::possible_movements_;
	state.actual_target_type = states::state_controller::actual_targeting_type_;

	state.button_bitmaps.fill(bitmap_key::none);

	auto id = board::at(states::state_controller::selected_index_);
	if (id != board::empty_id) {
		auto& bitmap_field = bitmap_field_manager::component_for(id);
		state.button_bitmaps[0] = bitmap_field.bmt_key;

		auto& abilities = abilities_manager::component_for(board::at(states::state_controller::selected_index_));
		for (std::size_t i = 1; i < 6; ++i) {
			auto ability = abilities.at(i - 1);
			if (ability) {
				state.button_bitmaps[i] = ability->get_bitmap_key();
			}
		}
	}

	state.entity_name = names_manager::component_for(board::at(states::state_controller::selected_index_));
	state.selected_index = states::state_controller::selected_index_;

	for (auto&& move : states::state_controller::possible_movements_) {
		if (states::state_controller::valid_target(move)) {
			state.valid_movements.insert(move);
		}
	}

	return std::move(state);
}

int main() {

	game g;

	server binder;

	animations_queue::set_pull_function([&binder](){
		binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));
	});

	sender::set_sender([&binder](sf::Packet packet) {
		binder.send_notification(packet);
	});

	std::vector<local_state> lstates(2);

	binder.bind(message_types::on_board, [&](sf::Packet& packet) {
		std::cout << "on_board\n";

		int client_id;
		size_t x;
		size_t y;

		packet >> client_id;
		packet >> x;
		packet >> y;

        bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {
			g.on_board(x, y);

		} else {
			std::cout << "on_board_2\n";

			g.on_board_2(x, y, lstates[client_id]);
		}

		binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));

		if (client_id == players_manager::get_active_player_id() || single_client) {
			binder.send_notification_to(client_id, make_packet(message_types::local_state, get_local_state(g)));

		} else {
			binder.send_notification_to(client_id, make_packet(message_types::local_state, lstates[client_id]));
		}


//		binder.send_notification_to((this_player_id + 1) % 2, make_packet("local_state", local_state()));

		binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));
	});

	binder.bind(message_types::on_button, [&](sf::Packet& packet) {
		std::cout << "on_button\n";

		int client_id;
		std::size_t n;

		packet >> client_id;
		packet >> n;

		const bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {
			g.on_button(n);

		} else {
			std::cout << "on_board_2\n";

			g.on_button_2(n, lstates[client_id]);
		}

		if (n == 5) {

			lstates = std::vector<local_state>(2);

			auto active_player = players_manager::get_active_player_id();

			sf::Packet result_packet;
			result_packet << "end_turn" << active_player;

			binder.send_notification(result_packet);
		}

		binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));

		if (n == 5) {

            if (single_client) {
                binder.send_notification_to(client_id, make_packet(message_types::local_state, get_local_state(g)));
            } else {
                binder.send_notification_to(players_manager::get_active_player_id(), make_packet(message_types::local_state, get_local_state(g)));
                binder.send_notification_to((players_manager::get_active_player_id() + 1) % 2, make_packet(message_types::local_state, local_state()));
            }

		} else {

			if (client_id == players_manager::get_active_player_id() || single_client) {
				binder.send_notification_to(client_id, make_packet(message_types::local_state, get_local_state(g)));

			} else {
				binder.send_notification_to(client_id, make_packet(message_types::local_state, lstates[client_id]));
			}
		}

//		binder.send_notification_to((players::active_player_index()) % 2, make_packet("local_state", get_local_state(g)));
//		binder.send_notification_to((players::active_player_index() + 1) % 2, make_packet("local_state", local_state()));

		binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));
	});

	binder.bind(message_types::get_button_description, [&](sf::Packet& packet) {
		std::cout << "get_button_description\n";

		int client_id;
		std::size_t n;

		packet >> client_id;
		packet >> n;

		std::string description;

		const bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {

			description = g.get_button_description(states::state_controller::selected_index_, n);

		} else {

			description = g.get_button_description(lstates[client_id].selected_index, n);
		}

		if (single_client) {
			binder.send_notification_to(client_id, make_packet(message_types::description, description));
		} else {
			binder.send_notification_to(players_manager::get_active_player_id(), make_packet(message_types::description, description));
			binder.send_notification_to((players_manager::get_active_player_id() + 1) % 2, make_packet(message_types::description, description));
		}
	});

	binder.start();

	binder.working_thread.join();

	return 0;
}