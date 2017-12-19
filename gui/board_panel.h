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
	using rect_type = sf::Rect<int>;

	void prepare();
	void draw(sf::RenderWindow& window);
	bool is_hit(const point_type& cursor) const;
	std::pair<size_t, size_t> hit_field(const point_type& cursor) const;

private:
	std::vector<my_button> buttons_;
	sf::Texture grass_texture_;
};

board_panel::point_type board_indexies_to_point(size_t col, size_t row);
board_panel::rect_type board_indexies_to_rectangle(size_t col, size_t row);
board_panel::point_type board_indexies_to_point(double col, double row);
board_panel::rect_type board_indexes_to_rectangle(double col, double row);

board_panel::point_type board_index_to_point(size_t index);
board_panel::rect_type board_index_to_rectangle(size_t index);

size_t indexes_to_index(size_t row, size_t col);
std::pair<size_t, size_t> index_to_indexes(size_t index);
};

#endif