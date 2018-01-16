#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <common/game_state.h>
#include "board.h"

class game
{
public:
	game();
	void initialize(std::array<std::vector<std::uint64_t>, board::cols_n * board::rows_n>& x);
	void on_board(std::uint64_t col, std::uint64_t row);
	void on_button(std::uint64_t n);
	std::string get_button_description(std::uint64_t selected_index, std::uint64_t n);

	void defeat();
	void victory();
};

#endif