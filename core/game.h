#ifndef GAME_H
#define GAME_H

#include <cstddef>

class game
{
public:
	game();
	void on_board(std::size_t col, std::size_t row);
	void on_button(std::size_t n);

	bool valid_target(std::size_t target_index) const;

	void defeat();
	void victory();

private:
	void create_werewolf();
};

#endif