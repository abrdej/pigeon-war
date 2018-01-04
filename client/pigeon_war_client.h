#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "gui/my_button.h"
#include "gui/board_panel.h"
#include "gui/buttons_panel.h"
#include "gui/entities_renderer.h"
#include "common/states.h"
#include "animation/animation_impl.h"
#include <atomic>
#include <common/turn_status.h>
#include "common/game_state.h"
#include "gui/drawer.h"

namespace view
{

class pigeon_war_client final
{
public:
	using point_type = sf::Vector2i;
public:
	pigeon_war_client();

	void run();

private:
	void update();
	void draw(sf::RenderWindow& window);
	void on_mouse_click(const point_type& args);

	void on_board(size_t col, size_t row);
	void on_button(size_t n);

	void prepare_animations();
	void update_for_entity();

private:
	//std::unique_ptr<rpc::client> client;
	sf::TcpSocket socket;
	sf::SocketSelector selector;

	static const int no_player_id = std::numeric_limits<int>::max();
	int player_id{no_player_id};

	turn_status last_turn_status{turn_status::update};

	friend class board_drawer;
	game_state state;

	sf::RenderWindow window_;
	board_panel board_panel_;
	buttons_panel buttons_panel_;
	animation::player_impl animation_player_impl_;
	std::unique_ptr<board_drawer> board_drawer_;
	entities_renderer entities_renderer_;
	std::atomic_bool block{false};
};

}

#endif