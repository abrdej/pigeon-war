#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <thread>
#include "gui/my_button.h"
#include "gui/board_panel.h"
#include "gui/buttons_panel.h"
//#include "labels_panel.h"
#include "animation/animation_impl.h"
#include "drawer.h"
#include <atomic>

class game;

namespace view
{
class gui final
{
public:
	using point_type = sf::Vector2i;
public:
	explicit gui(game& b);
	~gui();

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
	game& game_;
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