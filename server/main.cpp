#include <iostream>
#include <rpc/server.h>
#include <rpc/msgpack.hpp>
#include <core/board.h>
#include <core/states_controller.h>
#include <managers/abilities_manager.h>
#include <abilities/ability.h>
#include <core/animations_queue.h>
#include <core/players.h>
#include <chrono>
#include <thread>
#include <common/turn_status.h>
#include <SFML/Network.hpp>
#include "core/game.h"
#include "common/game_state.h"
#include "managers/bitmap_field_manager.h"
#include "managers/health_manager.h"
#include "managers/names_manager.h"
#include "Binder.h"
#include "common/packet_helper.h"

int function_impl(int a) {
	return a;
}

int main() {

	game g;

	std::atomic_int player_id{0};

	Binder binder;

	binder.bind("get_player_id", [&](sf::Packet&) {

		std::cout << "get_player_id\n";

		int new_player_id = player_id++;

		sf::Packet result_packet;
		result_packet << new_player_id;

		return result_packet;
	});

	binder.bind("get_status", [&](sf::Packet& packet) {

		std::cout << "get_status\n";

		int id;
		packet >> id;

		auto this_player_name = players::active_player_name();
		auto player_name = players::get_player_name_from_id(id);

		sf::Packet result_packet;
		result_packet << "status" << (this_player_name == player_name ? turn_status::do_turn : turn_status::wait);

		return result_packet;
	});

	binder.bind("get_board", [&](sf::Packet& packet) {
		std::cout << "get_board\n";

		std::array<std::vector<std::size_t>, board::cols_n * board::rows_n> fields;
		fields = board::fields_;

		sf::Packet result_packet;

		result_packet << fields;

		return result_packet;
	});

	binder.bind("get_entities_bitmaps", [&](sf::Packet& packet) {
		std::cout << "get_entities_bitmaps\n";

		sf::Packet result_packet;
		result_packet << bitmap_field_manager::get_map();

		return result_packet;
	});

	binder.bind("get_entities_healths", [&](sf::Packet& packet) {
		std::cout << "get_entities_healths\n";

		sf::Packet result_packet;
		result_packet << healths_manager::get_map();

		return result_packet;
	});

	binder.bind("pull_animations", [&](sf::Packet& packet) {

		int id;
		packet >> id;

		std::cout << "pull_animations\n";
		auto anim = animations_queue::pull_all(id);

		sf::Packet result_packet;
		result_packet << anim;

		return result_packet;
	});

	binder.bind("get_game_state", [&](sf::Packet& packet) {
		std::cout << "get_game_state\n";
		game_state state;
		state.healths = healths_manager::get_map();
		state.possible_movements = states::state_controller::possible_movements_;
		state.actual_target_type = states::state_controller::actual_targeting_type_;
		state.board.fields_ = board::fields_;

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

		state.entities_bitmaps = bitmap_field_manager::get_map();
		state.entity_name = names_manager::component_for(board::at(states::state_controller::selected_index_));
		state.selected_index = states::state_controller::selected_index_;

		for (auto&& move : states::state_controller::possible_movements_) {
			if (g.valid_target(move)) {
				state.valid_movements.insert(move);
			}
		}

		sf::Packet result_packet;
		result_packet << state;

		return result_packet;
	});

	binder.bind("on_board", [&](sf::Packet& packet) {
		std::cout << "on_board\n";

		size_t x;
		size_t y;

		packet >> x;
		packet >> y;

		g.on_board(x, y);

		sf::Packet result_packet;
		result_packet << "Fine";

		return result_packet;
	});

	binder.bind("on_button", [&](sf::Packet& packet) {
		std::cout << "on_button\n";

		std::size_t n;
		packet >> n;

		g.on_button(n);

		if (n == 5) {
			// end of turn
			// notify all clients of it

			binder.end_turn();
		}

		sf::Packet result_packet;
		result_packet << "Fine";

		return result_packet;
	});

	binder.start();

	binder.working_thread.join();

	return 0;
}