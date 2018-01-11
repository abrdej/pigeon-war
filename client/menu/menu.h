//
// Created by abrdej on 11.01.18.
//

#ifndef PIGEONWAR_MENU_H
#define PIGEONWAR_MENU_H


#include <SFML/Graphics.hpp>

class menu {
	sf::Font name_font;

public:
	menu();


	void draw(sf::RenderWindow& window);
};


#endif //PIGEONWAR_MENU_H
