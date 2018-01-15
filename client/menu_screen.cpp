#include "menu_screen.h"
#include <SFML/Window/Event.hpp>

menu_screen::menu_screen() {

}

int menu_screen::run(sf::RenderWindow& app) {

	sf::Event event;

	bool running = true;

	while (running) {

		while (app.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				return -1;

			} else if (event.type == sf::Event::MouseButtonReleased) {

				auto pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);


			}

		}
	}

}