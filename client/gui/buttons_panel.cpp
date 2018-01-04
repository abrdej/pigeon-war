#include <client/board_container.h>
#include "buttons_panel.h"
#include "view_constants.h"
#include "bitmap_center.h"

namespace view
{
sf::Texture buttons_panel::end_turn_bitmap_;

void buttons_panel::prepare()
{
    auto y_pos = constants::top_left_point.y + board_container::rows_n * constants::field_size;

    auto x_pos = constants::top_left_point.x + 2 * constants::field_size + constants::field_size / 2;

	for (size_t col = 0; col < 5; ++col)
	{
		my_button::point_type init_point(x_pos + col * constants::field_size,
                                         y_pos);
		buttons_.emplace_back(my_button::rect_type(init_point.x, init_point.y,
												   constants::field_size, constants::field_size));
	}

    buttons_.emplace_back(my_button::rect_type(constants::top_left_point.x + constants::field_size * (board_container::cols_n - 1),
                                               constants::top_left_point.y + constants::field_size * board_container::rows_n,
                                               constants::field_size, constants::field_size));

	end_turn_bitmap_.loadFromFile(resources_directory + "end_turn.png");
	buttons_[buttons_.size() - 1].icon(end_turn_bitmap_);

    name_font.loadFromFile(resources_directory + "verdanab.ttf");
}

void buttons_panel::draw(sf::RenderWindow& window)
{
	for (auto&& button : buttons_)
	{
		button.draw(window);
	}
    draw_hint(window);
}

bool buttons_panel::is_hit(sf::Vector2i cursor) const
{
	size_t y_pos = constants::top_left_point.y + board_container::rows_n * constants::field_size;
	size_t x_right = constants::top_left_point.x + board_container::cols_n * constants::field_size;

	return (cursor.x >= constants::top_left_point.x && cursor.y >= y_pos &&
			cursor.x <= x_right && cursor.y <= y_pos + constants::field_size);
}

size_t buttons_panel::hit_button(sf::Vector2i cursor) const
{
	//auto x_right = cursor.x - constants::top_left_point.x;
	//return x_right / constants::field_size;

    for (std::size_t i = 0; i < buttons_.size(); ++i) {
        if (buttons_[i].is_hit(cursor)) {
            return i;
        }
    }
    return std::numeric_limits<std::size_t>::max();
}

void buttons_panel::set_for_entity_for(const std::string& entity_name,
									   const std::array<bitmap_key, 6>& button_bitmaps) {

	this->entity_name = entity_name;

	for (std::size_t i = 1; i < 6; ++i) {
		if (button_bitmaps[i] != bitmap_key::none) {
			buttons_[i - 1].icon(bitmap_center::get_bitmap(button_bitmaps[i]));
		} else {
			buttons_[i - 1].remove_icon();
			hints[i - 1].clear();
		}
	}

	if (button_bitmaps[0] != bitmap_key::none) {
		entity_logo.setTexture(view::bitmap_center::get_bitmap(button_bitmaps[0]));
		entity_logo.setPosition(sf::Vector2f(constants::field_size / 4,
											 constants::top_left_point.y + (board_container::rows_n) * constants::field_size +
											 constants::field_size / 8));
	}
}

void buttons_panel::set_hint_for(const sf::Vector2f& pos, std::size_t hint_idx) {
    hint_button_idx = hint_idx;
    hint_pos = pos;
}

void buttons_panel::remove_hint() {
    hint_button_idx = no_hint;
}

void buttons_panel::draw_hint(sf::RenderWindow& window) {

    window.draw(entity_logo);

    sf::Text name;
    name.setFont(name_font);
    name.setCharacterSize(18);
    name.setColor(sf::Color::White);
    name.setPosition(sf::Vector2f(constants::field_size / 4,
                                  constants::top_left_point.y + (board_container::rows_n + 1) * constants::field_size + constants::field_size / 8));
    name.setString(entity_name);
    window.draw(name);

    if (hint_button_idx < 5) {
        sf::Text hint;
        hint.setFont(name_font);
        hint.setCharacterSize(18);
        hint.setColor(sf::Color::White);
        hint.setPosition(hint_pos + sf::Vector2f(constants::field_size / 2, 0.f));
        hint.setString(hints[hint_button_idx]);
        window.draw(hint);
    }
}

};