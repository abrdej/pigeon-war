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
#include <scenarios/scenarios.h>
#include <managers/additions_manager.h>
#include "core/game.h"
#include "common/game_state.h"
#include "managers/bitmap_field_manager.h"
#include "managers/health_manager.h"
#include "managers/names_manager.h"
#include "server.h"
#include "common/packet_helper.h"
#include "sender.h"
#include "cbor/cbor.h"

game_state get_game_state(game& g) {

	game_state state;
	state.healths = healths_manager::get_map();

	for (sf::Uint64 i = 0; i < board::fields_.size(); ++i) {
		for (auto&& elem : board::fields_[i]) {
			state.board.fields_[i].push_back(elem);
		}
	}

	state.entities_bitmaps = bitmap_field_manager::get_map();
	state.entities_additional_effects = additions_manager::get_map();

	return std::move(state);
}

local_state get_local_state(game& g) {

	local_state state;

	for (auto&& idx : states::state_controller::possible_movements_)
		state.possible_movements.push_back(idx);

	state.actual_target_type = states::state_controller::actual_targeting_type_;

	state.button_bitmaps.fill(bitmap_key::none);

	auto id = board::at(states::state_controller::selected_index_);
	if (id != board::empty_id) {
		auto& bitmap_field = bitmap_field_manager::component_for(id);
		state.button_bitmaps[0] = bitmap_field.bmt_key;

		auto& abilities = abilities_manager::component_for(board::at(states::state_controller::selected_index_));
		for (sf::Uint64 i = 1; i < 6; ++i) {
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

	create_scenario(g,  "saurions_web");

	server binder;

	animations_queue::set_pull_function([&binder](){
		binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));
	});

	sender::set_sender([&binder](sf::Packet packet) {
		binder.send_notification(packet);
	});

	std::vector<local_state> lstates(2);

	binder.bind(message_types::on_board, [&](sf::Packet& packet) {

		sf::Int32 client_id;
		sf::Uint64 x;
		sf::Uint64 y;

		packet >> client_id;
		packet >> x;
		packet >> y;

        bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {
			g.on_board(x, y);

			binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));
			binder.send_notification(make_packet(message_types::local_state, get_local_state(g)));
			binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));

		}
	});

	binder.bind(message_types::on_button, [&](sf::Packet& packet) {

		sf::Int32 client_id;
		sf::Uint64 n;

		packet >> client_id;
		packet >> n;

		const bool single_client = binder.is_single_client();

		if (client_id == players_manager::get_active_player_id() || single_client) {
			g.on_button(n);

			if (n == 5) {

				lstates = std::vector<local_state>(2);

				auto active_player = players_manager::get_active_player_id();

				sf::Packet result_packet;
				result_packet << "end_turn" << active_player;

				binder.send_notification(result_packet);
			}

			binder.send_notification(make_packet(message_types::animations, animations_queue::pull_all()));

			binder.send_notification(make_packet(message_types::local_state, get_local_state(g)));
			binder.send_notification(make_packet(message_types::game_state, get_game_state(g)));


		}
	});

	binder.bind(message_types::get_button_description, [&](sf::Packet& packet) {

		sf::Int32 client_id;
		sf::Uint64 n;

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