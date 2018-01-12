//
// Created by abrdej on 12.01.18.
//

#ifndef PIGEONWAR_HINT_H
#define PIGEONWAR_HINT_H

#include <SFML/Graphics.hpp>

class hint {
	sf::Font font;
	sf::RectangleShape shape;
	sf::Text text;


public:
	hint(const sf::Vector2i& pos, const std::string& str);
	void draw(sf::RenderWindow& window);
};


#endif //PIGEONWAR_HINT_H
