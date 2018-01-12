#ifndef BOARD_PANEL_H
#define BOARD_PANEL_H

#include <SFML/Graphics.hpp>
#include "my_button.h"

namespace view
{

class board_panel final
{
public:
	using point_type = sf::Vector2i;
	using rect_type = sf::Rect<sf::Int32>;

	void prepare();
	void draw(sf::RenderWindow& window);
	bool is_hit(const point_type& cursor) const;
	std::pair<sf::Uint64, sf::Uint64> hit_field(const point_type& cursor) const;

private:
	std::vector<my_button> buttons_;
	sf::Texture grass_texture_;
};

board_panel::point_type board_indexies_to_point(sf::Uint64 col, sf::Uint64 row);
board_panel::rect_type board_indexies_to_rectangle(sf::Uint64 col, sf::Uint64 row);
board_panel::point_type board_indexies_to_point(double col, double row);
board_panel::rect_type board_indexes_to_rectangle(double col, double row);

board_panel::point_type board_index_to_point(sf::Uint64 index);
board_panel::rect_type board_index_to_rectangle(sf::Uint64 index);

sf::Uint64 indexes_to_index(sf::Uint64 row, sf::Uint64 col);
std::pair<sf::Uint64, sf::Uint64> index_to_indexes(sf::Uint64 index);
};

#endif