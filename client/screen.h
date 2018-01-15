//
// Created by abrdej on 15.01.18.
//

#ifndef PIGEONWAR_SCREEN_H
#define PIGEONWAR_SCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>

struct screen {
	virtual int run(sf::RenderWindow& app) = 0;
};

#endif //PIGEONWAR_SCREEN_H
