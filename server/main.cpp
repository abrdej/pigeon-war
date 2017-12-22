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
#include "core/game.h"
#include "common/game_state.h"
#include "managers/bitmap_field_manager.h"
#include "managers/health_manager.h"
#include "managers/names_manager.h"

int main() {

	game g;

	rpc::server server(8080);

	std::atomic_int player_id{0};

	server.bind("get_player_id", [&]() {
		std::cout << "get_player_id\n";
		return player_id++;
	});

	server.bind("get_status", [&](int id) -> turn_status {

		std::cout << "get_status\n";

		auto this_player_name = players::active_player_name();
		auto player_name = players::get_player_name_from_id(id);

		return this_player_name == player_name ? turn_status::do_turn : turn_status::wait;
	});

	server.bind("wait_for_turn", [&]() {

		players::active_player_name();

		std::this_thread::sleep_for(std::chrono::seconds(5));
	});

	server.bind("get_board", [&]() {
		std::cout << "get_board\n";
		return board::fields_;
	});

	server.bind("get_entities_bitmaps", [&]() {
		std::cout << "get_entities_bitmaps\n";
		return bitmap_field_manager::get_map();
	});

	server.bind("get_entities_healths", [&]() {
		std::cout << "get_entities_healths\n";
		return healths_manager::get_map();
	});

	server.bind("get_game_state", [&]() {
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

		return state;
	});

	server.bind("on_board", [&](size_t x, size_t y) {
		std::cout << "on_board\n";
		g.on_board(x, y);
	});

	server.bind("pull_animations", [&](int id) {
		std::cout << "pull_animations\n";
		auto anim = animations_queue::pull_all(id);

		return anim;
	});

	server.bind("on_button", [&](size_t n) {
		std::cout << "on_button\n";
		g.on_button(n);
	});

	server.run();

	return 0;
}