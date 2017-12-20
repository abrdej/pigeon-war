#include <iostream>
#include <rpc/server.h>
#include <rpc/msgpack.hpp>
#include <core/board.h>
#include <core/states_controller.h>
#include <managers/abilities_manager.h>
#include <abilities/ability.h>
#include <core/animations_queue.h>
#include "core/game.h"
#include "common/game_state.h"
#include "managers/bitmap_field_manager.h"
#include "managers/health_manager.h"
#include "managers/names_manager.h"

int main() {

	game g;

	rpc::server server(8080);

	server.bind("get_board", [&]() {
		return board::fields_;
	});

	server.bind("get_entities_bitmaps", [&]() {
		return bitmap_field_manager::get_map();
	});

	server.bind("get_entities_healths", [&]() {
		return healths_manager::get_map();
	});

	server.bind("get_game_state", [&]() {
		game_state state;
		state.healths = healths_manager::get_map();
		state.possible_movements = states::state_controller::possible_movements_;
		state.actual_target_type = states::state_controller::actual_targeting_type_;
		state.board.fields_ = board::fields_;

		state.button_bitmaps.fill(bitmap_key::none);

		auto& bitmap_field = bitmap_field_manager::component_for(board::at(states::state_controller::selected_index_));
		state.button_bitmaps[0] = bitmap_field.bmt_key;

		auto& abilities = abilities_manager::component_for(board::at(states::state_controller::selected_index_));
		for (std::size_t i = 1; i < 6; ++i) {
			auto ability = abilities.at(i - 1);
			if (ability) {
				state.button_bitmaps[i] = ability->get_bitmap_key();
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
		g.on_board(x, y);
	});

	server.bind("pull_animations", [&]() {
		return animations_queue::pull_all();
	});

	server.bind("on_button", [&](size_t n) {
		g.on_button(n);
	});

	server.run();

	return 0;
}