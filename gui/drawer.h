#ifndef DRAWER_H
#define DRAWER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "gui/bitmap_center.h"
#include "core/board.h"
#include "managers/entity_manager.h"
#include "core/states.h"
#include "core/game.h"
#include "gui/view_constants.h"
#include "gui/board_panel.h"
#include "managers/health_manager.h"
#include "managers/directions_manager.h"
#include "managers/types_manager.h"

struct stone;

namespace view
{
	class entities_renderer
	{
		struct render_data
		{
			sf::Sprite sprite;
			int health;
			sf::Vector2f health_pos;
		};

	public:
		entities_renderer()
		{
			font_.loadFromFile("verdanab.ttf");
		}

		void render(sf::RenderWindow& window)
		{
			prepare_render(window);
			
			for (auto& render_item : render_data_)
			{
				window.draw(render_item.sprite);
				render_text(render_item.health, render_item.health_pos, window);
			}
		}
		void prepare_render(sf::RenderWindow& window)
		{
			render_data_.clear();
			std::size_t last_col{std::numeric_limits<std::size_t>::max()};
			std::size_t last_row{std::numeric_limits<std::size_t>::max()};
            board::for_each([this, &window, &last_col, &last_row](size_t entity_id, size_t col, size_t row) {
                if (entity_id != -1) {
                    render_data data{};
                    data.sprite.setTexture(bitmap_center::get_image_for_entity(
                            types_manager::component_for(entity_id)));

                    auto position = sf::Vector2f(board_indexies_to_point(col, row));
                    data.sprite.setPosition(position);
                    data.sprite.setTextureRect(directions_manager::component_for(entity_id)
                                               == entity_definition::directions::left ? sf::IntRect(60, 0, -60, 60)
                                                                                      : sf::IntRect(0, 0, 60, 60));

                    data.health = healths_manager::component_for(entity_id).health;
                    position.x += view::constants::field_size / 4.f;
                    position.y -= view::constants::field_size / 4.f;

					if (last_col == col && last_row == row) {
						position.x += view::constants::field_size / 4.f;
						position.y += view::constants::field_size / 4.f;
					}

                    data.health_pos = position;
                    render_data_.push_back(data);

					last_col = col;
					last_row = row;
                }
            });
		}

		void render_text(size_t entity_health, sf::Vector2f position, sf::RenderWindow& window)
		{
			if (entity_health == indestructible)
				return;
			
			sf::Text text;
			text.setFont(font_);
			text.setString(std::to_string(entity_health));
			text.setCharacterSize(18);
			text.setColor(sf::Color::Black);
			text.setPosition(position);
			
			//sf::FloatRect background_rect = text.getGlobalBounds();
			//sf::RectangleShape background(sf::Vector2f(background_rect.width, background_rect.height));
			//background.setFillColor(sf::Color(220, 220, 220, 255));
			//window.draw(background, text.getTransform());
			window.draw(text);
		}
	private:
		std::vector<render_data> render_data_;
		sf::Font font_;
	};


	struct draw_data
	{
		enum class directions { right, left };
		using sprite = sf::Sprite;
		sprite sprite_;
		directions direction_;
	};

	class board_drawer
	{
	public:
		board_drawer(game& game, sf::RenderWindow& window)
			: game_(game),
			window_(window)
		{}
		void draw()
		{
			draw_selection(states::state_controller::selected_index_);
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
			for (auto& elem : states::state_controller::possible_movements_)
				draw_possible_movement(elem);
		}
		void draw_possible_movement(size_t index)
		{
			if (states::state_controller::actual_targeting_type_ == states::target_types::non)
				return;

			sf::Sprite sprite;

			if (states::state_controller::actual_targeting_type_ == states::target_types::moving)
				sprite.setTexture(bitmap_center::grass_move_bitmap);
			else if (states::state_controller::actual_targeting_type_ == states::target_types::enemy)
			{
				if (game_.valid_target(index))
					sprite.setTexture(bitmap_center::grass_damage_bitmap);
				else
					sprite.setTexture(bitmap_center::grass_attack_bitmap);
			}

			auto pos = board_index_to_point(index);
			sprite.setPosition(sf::Vector2f(pos.x, pos.y));
			window_.draw(sprite);
		}

	private:
		game& game_;
		sf::RenderWindow& window_;
		std::vector<draw_data> draw_data_;
	};
};
#endif