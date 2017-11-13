#ifndef BUTTONS_PANEL_H
#define BUTTONS_PANEL_H

#include "my_button.h"
#include <SFML/Graphics.hpp>

class entity;
class entity_manager;

namespace view
{
	class buttons_panel final
	{
	public:
		void prepare();
		void draw(sf::RenderWindow& window);
		bool is_hit(sf::Vector2i cursor) const;
		size_t hit_button(sf::Vector2i cursor) const;
		void set_buttons_for(size_t entity_id);

	private:
		std::vector<my_button> buttons_;
		std::vector<sf::Sprite> sprites_;
		static sf::Texture end_turn_bitmap_;
	};
};

/*
#include <nana\gui.hpp>
#include "my_button.h"

class entity;

namespace view
{
	class buttons_panel final
	{
	public:
		void prepare();
		void draw(nana::paint::graphics& graph);
		bool is_hit(const nana::point& cursor) const;
		size_t hit_button(const nana::point& cursor) const;
		void set_buttons_for(const entity& entity);

	private:
		std::vector<my_button> buttons_;
		std::vector<nana::paint::image> icons_;
	};
};*/
#endif