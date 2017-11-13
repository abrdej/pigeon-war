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
}

#endif