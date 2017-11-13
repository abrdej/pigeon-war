#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

namespace view
{
	class my_button final
	{
	public:
		using point_type = sf::Vector2i;
		using rect_type = sf::Rect<int>;
		using bitmap_type = sf::Texture;


		my_button(const point_type& center, size_t size, const std::function<void()>& callback = nullptr);
		my_button(const rect_type& rect, const std::function<void()>& callback = nullptr);

		inline bool is_hit(const point_type& pt);
		void draw(sf::RenderWindow& window);
		void add_callback(const std::function<void()>& func = nullptr);
		void icon(const bitmap_type& img);
		void remove_icon();

	private:
		std::function<void()> callback_;
		rect_type position_;
		sf::Sprite sprite_;
	};
};

/*#include <nana\gui.hpp>

namespace view
{
	class my_button final
	{
	public:
		my_button(const nana::point& center, size_t size, const std::function<void()>& callback = nullptr);
		my_button(const nana::rectangle& rect, const std::function<void()>& callback = nullptr);

		inline bool is_hit(const nana::point& pt);
		void draw(nana::paint::graphics& graph);
		void add_callback(const std::function<void()>& func = nullptr);
		void icon(const nana::paint::image& img);
		void remove_icon();

	private:
		std::function<void()> callback_;
		nana::rectangle position_;
		nana::paint::image img_;
	};
};
*/
#endif