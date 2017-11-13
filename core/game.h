#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "managers/entity_manager.h"
#include "turn.h"
#include "core/states.h"
#include "players.h"
#include "entities/shooter.h"
#include "entities/wolf.h"

class game
{
public:
	game();
	void on_board(size_t col, size_t row);
	void on_button(size_t n);

	bool valid_target(size_t target_index) const;

	void defeat();
	void victory();

private:
	bool player_entity(size_t entity_index) const;
	bool enemy_entity(size_t entity_index) const;
	bool caster_entity(size_t entity_index) const;
	size_t activ_player_first_entity_index();
	void create_werewolf();
};

#endif