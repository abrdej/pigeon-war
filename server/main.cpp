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
#include "server.h"
#include "common/packet_helper.h"

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
		if (g.valid_target(move)) {
			state.valid_movements.insert(move);
		}
	}

	return std::move(state);
}

int main() {

	game g;

	server binder;

	std::vector<local_state> lstates(2);

	binder.bind("on_board", [&](sf::Packet& packet) {
		std::cout << "on_board\n";

		int this_player_id;
		size_t x;
		size_t y;

		packet >> this_player_id;
		packet >> x;
		packet >> y;

		if (this_player_id == players::active_player_index()) {
			g.on_board(x, y);

		} else {
			std::cout << "on_board_2\n";

			g.on_board_2(x, y, lstates[this_player_id]);
		}

		binder.send_notification(make_packet("animations", animations_queue::pull_all(0)));

		if (this_player_id == players::active_player_index()) {
			binder.send_notification_to(this_player_id, make_packet("local_state", get_local_state(g)));

		} else {
			binder.send_notification_to(this_player_id, make_packet("local_state", lstates[this_player_id]));
		}


//		binder.send_notification_to((this_player_id + 1) % 2, make_packet("local_state", local_state()));

		binder.send_notification(make_packet("game_state", get_game_state(g)));
	});

	binder.bind("on_button", [&](sf::Packet& packet) {
		std::cout << "on_button\n";

		int this_player_id;
		std::size_t n;

		packet >> this_player_id;
		packet >> n;

		g.on_button(n);

		if (n == 5) {
			auto active_player = players::active_player_index();

			sf::Packet result_packet;
			result_packet << "end_turn" << active_player;

			binder.send_notification(result_packet);
		}

		binder.send_notification(make_packet("animations", animations_queue::pull_all(0)));

		binder.send_notification_to((players::active_player_index()) % 2, make_packet("local_state", get_local_state(g)));
		binder.send_notification_to((players::active_player_index() + 1) % 2, make_packet("local_state", local_state()));

		binder.send_notification(make_packet("game_state", get_game_state(g)));
	});

	binder.start();

	binder.working_thread.join();

	return 0;
}