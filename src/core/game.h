#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <core/game_state.h>
#include "board.h"

class game
{
public:
	game();
	void on_board(std::uint32_t col, std::uint32_t row);
	void on_button(std::uint32_t n);
	std::string get_button_description(std::uint32_t selected_index, std::uint32_t n);

	void defeat();
	void victory();
};

#endif