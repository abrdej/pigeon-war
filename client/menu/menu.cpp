#include "menu.h"
#include <SFML/Graphics/Text.hpp>
#include <config.h>

menu::menu() {
	name_font.loadFromFile(resources_directory + "verdanab.ttf");
}

void menu::draw(sf::RenderWindow& window) {

	sf::Text name;
	name.setFont(name_font);
	name.setCharacterSize(18);
	name.setColor(sf::Color::White);
	name.setPosition(sf::Vector2f(0, 0));
	name.setString("Scenarios:");
	window.draw(name);
}

