#include "gui/gui.h"
#include "core/game.h"
#include "gui/bitmap_center.h"
#include <SFML/Graphics.hpp>
#include "entities/wolf.h"

//view::bitmap_center::load();
//game game;
//view::gui g(game);
//nana::exec();

int main()
{
	view::bitmap_center::load();

	game game;
	view::gui g(game);
	g.run();

	/*
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Sprite sprite;
		auto texture = view::bitmap_center::get_image_for_entity<wolf>();
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(0, 0));
		window.clear();
		window.draw(sprite);
		window.display();
	}*/

	return 0;
};