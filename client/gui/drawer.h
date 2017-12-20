#ifndef DRAWER_H
#define DRAWER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "client/gui/bitmap_center.h"
#include "client/gui/view_constants.h"
#include "client/gui/board_panel.h"
#include "drawing_manager.h"
#include "common/game_state.h"
#include "common/states.h"

namespace view
{

class board_drawer
{
public:
	board_drawer(game_state& state, sf::RenderWindow& window)
			: state(state),
			  window_(window)
	{}
	void draw()
	{
		draw_selection(state.selected_index);
		draw_possible_movements();
	}

private:
	void draw_selection(size_t selection)
	{
		if (selection == states::no_selected_index)
			return;

		auto pos = board_index_to_point(selection);
		sf::Sprite sprite;
		sprite.setPosition(static_cast<sf::Vector2f>(pos));
		sprite.setTexture(bitmap_center::grass_selected_bitmap);
		window_.draw(sprite);
	}
	void draw_possible_movements()
	{
		for (auto& possible_movement : state.possible_movements)
			draw_possible_movement(possible_movement);
	}
	void draw_possible_movement(size_t index)
	{
		if (state.actual_target_type == states::target_types::non)
			return;

		sf::Sprite sprite;

		if (state.actual_target_type == states::target_types::moving)
			sprite.setTexture(bitmap_center::grass_move_bitmap);
		else if (state.actual_target_type == states::target_types::enemy)
		{
			if (state.valid_movements.find(index) != std::end(state.valid_movements))
				sprite.setTexture(bitmap_center::grass_damage_bitmap);
			else
				sprite.setTexture(bitmap_center::grass_attack_bitmap);
		} else if (state.actual_target_type == states::target_types::friendly)
		{
			if (state.valid_movements.find(index) != std::end(state.valid_movements))
				sprite.setTexture(bitmap_center::grass_boost_bitmap);
			else
				sprite.setTexture(bitmap_center::grass_friendly_bitmap);
		}else {
			sprite.setTexture(bitmap_center::grass_move_bitmap);
		}

		auto pos = board_index_to_point(index);
		sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		window_.draw(sprite);
	}

private:
	game_state& state;
	sf::RenderWindow& window_;
};
};
#endif