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

		for (size_t col = 0; col < board::cols_n; ++col)
		{
			my_button::point_type init_point(constants::top_left_point.x + col * constants::field_size,
				y_pos);
			buttons_.emplace_back(my_button::rect_type(init_point.x, init_point.y,
				constants::field_size, constants::field_size));
		}
		end_turn_bitmap_.loadFromFile("end_turn.png");
		buttons_[buttons_.size() - 1].icon(end_turn_bitmap_);
	}

	void buttons_panel::draw(sf::RenderWindow& window)
	{
		for (auto&& button : buttons_)
		{
			button.draw(window);
		}
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
		auto x_right = cursor.x - constants::top_left_point.x;
		return x_right / constants::field_size;
	}

	void buttons_panel::set_buttons_for(size_t entity_id)
	{
		auto& entity_abilities = abilities_manager::component_for(entity_id);
		for (std::size_t i = 0; i < 5; ++i)
		{
			auto ability = entity_abilities.at(i);
            if (ability) {
                buttons_[i].icon(bitmap_center::get_image_for_entity(*ability));
            } else {
				buttons_[i].remove_icon();
			}
		}
	}
};