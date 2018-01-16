#include <config.h>
#include "board_panel.h"
#include "core/board.h"
#include "view_constants.h"

namespace view
{
void board_panel::prepare()
{
    grass_texture_.loadFromFile(resources_directory + "grass2.png");

    for (std::uint32_t row = 0; row < board::rows_n; ++row)
    {
        for (std::uint32_t col = 0; col < board::cols_n; ++col)
        {
            //point_type init_point(constants::top_left_point.x + col * constants::field_size,
            //	constants::top_left_point.y + row * constants::field_size);
            point_type init_point(col * constants::field_size, row * constants::field_size);

            buttons_.emplace_back(my_button(rect_type(init_point.x, init_point.y,
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
    for (auto&& button : buttons_) {
        button.draw(window);
    }
}

bool board_panel::is_hit(const point_type& cursor) const
{
    auto bottom_right_point = point_type(board::cols_n * constants::field_size, board::rows_n * constants::field_size);
    return (cursor.x >= 0 && cursor.y >= 0 &&
            cursor.x <= bottom_right_point.x && cursor.y <= bottom_right_point.y);
}

std::pair<std::uint32_t, std::uint32_t> board_panel::hit_field(const point_type& cursor) const
{
//		auto top_right_board_point = cursor; //  -constants::top_left_point;
//		std::uint32_t col = top_right_board_point.x / constants::field_size;
//		std::uint32_t row = top_right_board_point.y / constants::field_size;
//		return std::make_pair(col, row);
    for (std::uint32_t i = 0; i < buttons_.size(); ++i) {
        if (buttons_[i].is_hit(cursor)) {
            return index_to_indexes(i);
        }
    }
    return {};
}

board_panel::point_type board_indexies_to_point(std::uint32_t col, std::uint32_t row)
{
    std::int32_t x = constants::top_left_point.x + col * constants::field_size;
    std::int32_t y = constants::top_left_point.y + row * constants::field_size;
    return {x, y};
}

board_panel::rect_type board_indexies_to_rectangle(std::uint32_t col, std::uint32_t row)
{
    auto point = board_indexies_to_point(col, row);
    return {point.x, point.y, constants::field_size, constants::field_size};
}

board_panel::point_type board_indexies_to_point(double col, double row)
{
    std::int32_t x = constants::top_left_point.x + col * constants::field_size;
    std::int32_t y = constants::top_left_point.y + row * constants::field_size;
    return {x, y};
}

board_panel::rect_type board_indexes_to_rectangle(double col, double row)
{
    auto point = board_indexies_to_point(col, row);
    return {point.x, point.y, constants::field_size, constants::field_size};
}

board_panel::point_type board_index_to_point(std::uint32_t index)
{
    auto indexes = board::to_pos(index);
    return board_indexies_to_point(indexes.first, indexes.second);
}

board_panel::rect_type board_index_to_rectangle(std::uint32_t index)
{
    auto indexes = board::to_pos(index);
    return board_indexies_to_rectangle(indexes.first, indexes.second);
}

std::uint32_t indexes_to_index(std::uint32_t row, std::uint32_t col)
{
    return row * board::cols_n + col;
}

std::pair<std::uint32_t, std::uint32_t> index_to_indexes(std::uint32_t index)
{
    return std::make_pair(index % board::cols_n,
                          index / board::cols_n);
}
}