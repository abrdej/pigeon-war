#include "board_panel.h"
#include "core/board.h"
#include "view_constants.h"

namespace view
{
	void board_panel::prepare()
	{
		grass_texture_.loadFromFile("grass2.png");

		for (size_t row = 0; row < board::rows_n; ++row)
		{
			for (size_t col = 0; col < board::cols_n; ++col)
			{
				//point_type init_point(constants::top_left_point.x + col * constants::field_size,
				//	constants::top_left_point.y + row * constants::field_size);
				point_type init_point(col * constants::field_size, row * constants::field_size);

				buttons_.push_back(my_button(rect_type(init_point.x, init_point.y,
					constants::field_size, constants::field_size)));
				for (auto& button : buttons_)
				{
					button.icon(grass_texture_);
				}
			}
		}
	}

	void board_panel::draw(sf::RenderWindow& window)
	{
		std::for_each(std::begin(buttons_), std::end(buttons_), [&window](my_button& bttn)
		{
			bttn.draw(window);
		});
	}

	bool board_panel::is_hit(const point_type& cursor) const
	{
		auto bottom_right_point = point_type(board::cols_n * constants::field_size, board::rows_n * constants::field_size);
		return (cursor.x >= 0 && cursor.y >= 0 &&
			cursor.x <= bottom_right_point.x && cursor.y <= bottom_right_point.y);
	}

	std::pair<size_t, size_t> board_panel::hit_field(const point_type& cursor) const
	{
		auto top_right_board_point = cursor; //  -constants::top_left_point;
		size_t col = top_right_board_point.x / constants::field_size;
		size_t row = top_right_board_point.y / constants::field_size;
		return std::make_pair(col, row);
	}

	board_panel::point_type board_indexies_to_point(size_t col, size_t row)
	{
		int x = constants::top_left_point.x + col * constants::field_size;
		int y = constants::top_left_point.y + row * constants::field_size;
		return board_panel::point_type(x, y);
	}

	board_panel::rect_type board_indexies_to_rectangle(size_t col, size_t row)
	{
		auto point = board_indexies_to_point(col, row);
		return board_panel::rect_type(point.x, point.y, constants::field_size, constants::field_size);
	}

	board_panel::point_type board_indexies_to_point(double col, double row)
	{
		int x = constants::top_left_point.x + col * constants::field_size;
		int y = constants::top_left_point.y + row * constants::field_size;
		return board_panel::point_type(x, y);
	}

	board_panel::rect_type board_indexies_to_rectangle(double col, double row)
	{
		auto point = board_indexies_to_point(col, row);
		return board_panel::rect_type(point.x, point.y, constants::field_size, constants::field_size);
	}

	board_panel::point_type board_index_to_point(size_t index)
	{
		auto indexies = board::to_col_row(index);
		return board_indexies_to_point(indexies.first, indexies.second);
	}

	board_panel::rect_type board_index_to_rectangle(size_t index)
	{
		auto indexies = board::to_col_row(index);
		return board_indexies_to_rectangle(indexies.first, indexies.second);
	}

	size_t indexies_to_index(size_t row, size_t col)
	{
		return row * board::cols_n + col;
	}

	std::pair<size_t, size_t> index_to_indexies(size_t index)
	{
		return std::make_pair(index % board::cols_n,
			index / board::cols_n);
	}

}

/*
#include "view_constants.h"
#include "board.h"
#include <algorithm>

namespace view
{
	void board_panel::prepare()
	{
		static const auto grass_img = nana::paint::image(L"grass2.png");

		for (size_t row = 0; row < board::rows_n; ++row)
		{
			for (size_t col = 0; col < board::cols_n; ++col)
			{
				nana::point init_point(constants::top_left_point.x + col * constants::field_size,
					constants::top_left_point.y + row * constants::field_size);

				buttons_.push_back(my_button(nana::rectangle(init_point.x, init_point.y,
					constants::field_size, constants::field_size)));
				for (auto& button : buttons_)
				{
					button.icon(grass_img);
				}
			}
		}
	}

	void board_panel::draw(nana::paint::graphics& graph)
	{
		std::for_each(std::begin(buttons_), std::end(buttons_), [&graph](my_button& bttn)
		{
			bttn.draw(graph);
		});
	}

	bool board_panel::is_hit(const nana::point& cursor) const
	{
		auto bottom_right_point = constants::top_left_point
			+ nana::point(board::cols_n * constants::field_size, board::rows_n * constants::field_size);
		return (cursor.x >= constants::top_left_point.x && cursor.y >= constants::top_left_point.y &&
			cursor.x <= bottom_right_point.x && cursor.y <= bottom_right_point.y);
	}

	std::pair<size_t, size_t> board_panel::hit_field(const nana::point& cursor) const
	{
		auto top_right_board_point = cursor - constants::top_left_point;
		size_t col = top_right_board_point.x / constants::field_size;
		size_t row = top_right_board_point.y / constants::field_size;
		return std::make_pair(col, row);
	}

	nana::point board_indexies_to_point(size_t col, size_t row)
	{
		int x = constants::top_left_point.x + col * constants::field_size;
		int y = constants::top_left_point.y + row * constants::field_size;
		return nana::point(x, y);
	}

	nana::rectangle board_indexies_to_rectangle(size_t col, size_t row)
	{
		auto point = board_indexies_to_point(col, row);
		return nana::rectangle(point.x, point.y, constants::field_size, constants::field_size);
	}

	nana::point board_indexies_to_point(double col, double row)
	{
		int x = constants::top_left_point.x + col * constants::field_size;
		int y = constants::top_left_point.y + row * constants::field_size;
		return nana::point(x, y);
	}

	nana::rectangle board_indexies_to_rectangle(double col, double row)
	{
		auto point = board_indexies_to_point(col, row);
		return nana::rectangle(point.x, point.y, constants::field_size, constants::field_size);
	}

	nana::point board_index_to_point(size_t index)
	{
		auto indexies = board::to_col_row(index);
		return board_indexies_to_point(indexies.first, indexies.second);
	}

	nana::rectangle board_index_to_rectangle(size_t index)
	{
		auto indexies = board::to_col_row(index);
		return board_indexies_to_rectangle(indexies.first, indexies.second);
	}

	size_t indexies_to_index(size_t row, size_t col)
	{
		return row * board::cols_n + col;
	}

	std::pair<size_t, size_t> index_to_indexies(size_t index)
	{
		return std::make_pair(index % board::cols_n,
			index / board::cols_n);
	}

};*/