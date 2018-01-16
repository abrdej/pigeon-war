#include "my_button.h"

namespace view
{
my_button::my_button(const point_type& center, std::uint32_t size, const std::function<void()>& callback)
		: position_(rect_type(center.x - size / 2, center.y - size / 2, size, size)),
		  callback_(callback)
{
}

my_button::my_button(const rect_type& rect, const std::function<void()>& callback)
		: position_(rect),
		  callback_(callback)
{

}

void my_button::add_callback(const std::function<void()>& func)
{
	callback_ = func;
}

void my_button::draw(sf::RenderWindow& window)
{
	sprite_.setPosition(sf::Vector2f(position_.left, position_.top));
	window.draw(sprite_);
	//if (img_)
	//{
	//	img_.paste(graph, position_.x, position_.y);
	//	//graph.rectangle(position_, false, nana::color(255, 255, 255));
	//}
	//else
	//	graph.rectangle(position_, false, nana::color(100, 100, 100));
}

void my_button::icon(const bitmap_type& img)
{
	sprite_.setTexture(img);
}

void my_button::remove_icon()
{
	sprite_ = sf::Sprite();
}
}