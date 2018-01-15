//
// Created by abrdej on 15.01.18.
//

#ifndef PIGEONWAR_MENU_SCREEN_H
#define PIGEONWAR_MENU_SCREEN_H

#include "screen.h"

class menu_screen : public screen {
public:
	menu_screen();
	int run(sf::RenderWindow& app) override;
};


#endif //PIGEONWAR_MENU_SCREEN_H
