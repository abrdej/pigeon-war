#include "hint.h"
#include <config.h>

hint::hint(const sf::Vector2i& pos, const std::string& str) {

	font.loadFromFile(resources_directory + "verdanab.ttf");

	text.setPosition(sf::Vector2f(pos));
	text.setCharacterSize(16);
	text.setString(str);
	text.setFont(font);
	text.setColor(sf::Color(25, 25, 25));

	auto hint_size = text.getLocalBounds();

	const float margin = 10.f;

	sf::Vector2f rect_pos(pos.x - margin, pos.y - hint_size.height - margin);
	text.setPosition(sf::Vector2f(pos.x, pos.y - hint_size.height - margin));

	shape.setPosition(rect_pos);
	shape.setSize(sf::Vector2f(hint_size.width + 3 * margin, hint_size.height + margin));
	shape.setFillColor(sf::Color(192, 192, 192, 225));
	shape.setOutlineColor(sf::Color(25, 25, 25));
	shape.setOutlineThickness(2.0);
}

void hint::draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
}