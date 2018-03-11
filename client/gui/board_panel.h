#ifndef BOARD_PANEL_H
#define BOARD_PANEL_H

#include "my_button.h"

namespace view
{

class board_panel final
{
public:
	using point_type = sf::Vector2i;
	using rect_type = sf::Rect<std::int32_t>;

	void prepare();
	void draw(sf::RenderWindow& window);
	bool is_hit(const point_type& cursor) const;
	std::pair<std::uint32_t, std::uint32_t> hit_field(const point_type& cursor) const;

private:
	std::vector<my_button> buttons_;
	sf::Texture grass_texture_;
};

board_panel::point_type board_indexies_to_point(std::uint32_t col, std::uint32_t row);
board_panel::rect_type board_indexies_to_rectangle(std::uint32_t col, std::uint32_t row);
board_panel::point_type board_indexies_to_point(double col, double row);
board_panel::rect_type board_indexes_to_rectangle(double col, double row);

board_panel::point_type board_index_to_point(std::uint32_t index);
board_panel::rect_type board_index_to_rectangle(std::uint32_t index);

std::uint32_t indexes_to_index(std::uint32_t row, std::uint32_t col);
std::pair<std::uint32_t, std::uint32_t> index_to_indexes(std::uint32_t index);
};

#endif