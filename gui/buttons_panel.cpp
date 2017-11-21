#include "buttons_panel.h"
#include "view_constants.h"
#include <algorithm>
#include "core/board.h"
#include "abilities/abilities.h"
#include "gui/bitmap_center.h"
#include "abilities/shoot.h"
#include "managers/entity_manager.h"
#include "managers/abilities_manager.h"

namespace view
{
sf::Texture buttons_panel::end_turn_bitmap_;

void buttons_panel::prepare()
{
	size_t y_pos = constants::top_left_point.y + board::rows_n * constants::field_size;

    size_t x_pos = constants::top_left_point.x + 2 * constants::field_size + constants::field_size / 2;

	for (size_t col = 0; col < 5; ++col)
	{
		my_button::point_type init_point(x_pos + col * constants::field_size,
                                         y_pos);
		buttons_.emplace_back(my_button::rect_type(init_point.x, init_point.y,
												   constants::field_size, constants::field_size));
	}

    buttons_.emplace_back(my_button::rect_type(constants::top_left_point.x + constants::field_size * (board::cols_n - 1),
                                               constants::top_left_point.y + constants::field_size * board::rows_n,
                                               constants::field_size, constants::field_size));

	end_turn_bitmap_.loadFromFile("end_turn.png");
	buttons_[buttons_.size() - 1].icon(end_turn_bitmap_);

    name_font.loadFromFile("verdanab.ttf");
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
	size_t y_pos = constants::top_left_point.y + board::rows_n * constants::field_size;
	size_t x_right = constants::top_left_point.x + board::cols_n * constants::field_size;

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

void buttons_panel::set_buttons_for(size_t entity_id)
{
	if (entity_manager::alive(entity_id)) {
		auto& entity_abilities = abilities_manager::component_for(entity_id);
		for (std::size_t i = 0; i < 5; ++i)
		{
			auto ability = entity_abilities.at(i);
			if (ability) {
				buttons_[i].icon(bitmap_center::get_image_for_entity(*ability));

                hints[i] = ability->hint();

			} else {
				buttons_[i].remove_icon();
                hints[i].clear();
			}
		}
		// this sometimes can happen
	} else {
		for (std::size_t i = 0; i < 5; ++i)
		{
			buttons_[i].remove_icon();
		}
	}
}

void buttons_panel::set_name_for(size_t entity_id) {
    if (entity_manager::alive(entity_id)) {
        entity_name = names_manager::component_for(entity_id);

        entity_logo.setTexture(view::bitmap_center::get_image_for_entity(types_manager::component_for(entity_id)));
        entity_logo.setPosition(sf::Vector2f(constants::field_size / 4,
                                             constants::top_left_point.y + (board::rows_n) * constants::field_size +
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
    name.setFillColor(sf::Color::White);
    name.setPosition(sf::Vector2f(constants::field_size / 4,
                                  constants::top_left_point.y + (board::rows_n + 1) * constants::field_size + constants::field_size / 8));
    name.setString(entity_name);
    window.draw(name);

    if (hint_button_idx < 5) {
        sf::Text hint;
        hint.setFont(name_font);
        hint.setCharacterSize(18);
        hint.setFillColor(sf::Color::White);
        hint.setPosition(hint_pos + sf::Vector2f(constants::field_size / 2, 0.f));
        hint.setString(hints[hint_button_idx]);
        window.draw(hint);
    }
}

};