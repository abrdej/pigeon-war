#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <common/game_state.h>
#include "board.h"

class game
{
public:
	game();
	void initialize(std::array<std::vector<sf::Uint64>, board::cols_n * board::rows_n>& x);
	void on_board(sf::Uint64 col, sf::Uint64 row);
//	void on_board_2(sf::Uint64 col, sf::Uint64 row, local_state& lstate);
	void on_button(sf::Uint64 n);
//	void on_button_2(sf::Uint64 n, local_state& lstate);
	std::string get_button_description(sf::Uint64 selected_index, sf::Uint64 n);

	void defeat();
	void victory();
};

#endif