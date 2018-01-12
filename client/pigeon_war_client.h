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
#include <gui/hint.h>
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
	void receive_messages();
	void draw(sf::RenderWindow& window);
	void on_mouse_click(const point_type& args, bool left);

	void on_board(sf::Uint64 col, sf::Uint64 row);
	void on_button(sf::Uint64 n);
	void get_button_description(sf::Uint64 n);

	void prepare_animations();
	void update_for_entity();

	void set_description(const std::string& desc);
	void set_effects();

private:
	sf::TcpSocket socket;
	sf::SocketSelector selector;

	static const sf::Int32 no_player_id = std::numeric_limits<sf::Int32>::max();
	sf::Int32 player_id{no_player_id};

	friend class board_drawer;
	game_state state;
	local_state lstate;

	sf::Vector2i desc_pos;

	sf::RenderWindow window_;
	board_panel board_panel_;
	buttons_panel buttons_panel_;
	std::unique_ptr<hint> hint_ptr;
	animation::player_impl animation_player_impl_;
	std::unique_ptr<board_drawer> board_drawer_;
	entities_renderer entities_renderer_;
	std::atomic_bool block{false};
};

}

#endif