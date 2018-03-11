#include <client/board_container.h>
#include "buttons_panel.h"
#include "view_constants.h"
#include "bitmap_center.h"
#include "drawing_manager.h"

namespace view
{
sf::Texture buttons_panel::end_turn_bitmap_;

void buttons_panel::prepare()
{
    auto y_pos = constants::top_left_point.y + board_container::rows_n * constants::field_size;

    auto x_pos = constants::top_left_point.x + 2 * constants::field_size + constants::field_size / 2;

	for (std::uint32_t col = 0; col < 5; ++col)
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
	std::uint32_t y_pos = constants::top_left_point.y + board_container::rows_n * constants::field_size;
	std::uint32_t x_right = constants::top_left_point.x + board_container::cols_n * constants::field_size;

	return (cursor.x >= constants::top_left_point.x && cursor.y >= y_pos &&
			cursor.x <= x_right && cursor.y <= y_pos + constants::field_size);
}

std::uint32_t buttons_panel::hit_button(sf::Vector2i cursor) const
{
	//auto x_right = cursor.x - constants::top_left_point.x;
	//return x_right / constants::field_size;

    for (std::uint32_t i = 0; i < buttons_.size(); ++i) {
        if (buttons_[i].is_hit(cursor)) {
            return i;
        }
    }
    return std::numeric_limits<std::uint32_t>::max();
}

void buttons_panel::set_for_entity_for(std::uint32_t entity_id,
                                       const std::string& entity_name,
									   const std::array<bitmap_key, 5>& button_bitmaps) {

	this->entity_name = entity_name;

	for (std::uint32_t i = 0; i < 5; ++i) {
		if (button_bitmaps[i] != "none) {
			buttons_[i].icon(bitmap_center::get_bitmap(button_bitmaps[i]));
		} else {
			buttons_[i].remove_icon();
			hints[i].clear();
		}
	}

	if (entity_id != std::numeric_limits<decltype(entity_id)>::max()) {
        auto bitmap_key = drawing_manager::get_bitmap_key_for(entity_id);
		entity_logo.setTexture(view::bitmap_center::get_bitmap(bitmap_key));
		entity_logo.setPosition(sf::Vector2f(constants::field_size / 4,
											 constants::top_left_point.y + (board_container::rows_n) * constants::field_size +
											 constants::field_size / 8));
	}
}

void buttons_panel::set_hint_for(const sf::Vector2f& pos, std::uint32_t hint_idx) {
    hint_button_idx = hint_idx;
    hint_pos = pos;
}

void buttons_panel::set_description(const std::string& desc) {
	hint = desc;
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

	auto y_pos = constants::top_left_point.y + board_container::rows_n * constants::field_size;
	auto x_pos = constants::top_left_point.x + 2 * constants::field_size + constants::field_size / 2;

	sf::Vector2f init_point(x_pos + 5 * constants::field_size,
							y_pos + constants::field_size / 8);

	sf::Text thint;
	thint.setFont(name_font);
	thint.setCharacterSize(12);
	thint.setColor(sf::Color::White);
	thint.setPosition(init_point);
	thint.setString(hint);
	window.draw(thint);
}

};