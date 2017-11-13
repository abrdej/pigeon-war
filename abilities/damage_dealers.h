#ifndef DAMAGE_DEALERS_H
#define DAMAGE_DEALERS_H

#include "core/board.h"

namespace damage_dealers
{
	int random_damage(size_t damage);

	void play_change_helath_animation(size_t to_index, int change_health);

	int standard_damage_dealer(int damage, size_t to_index);
};

#endif