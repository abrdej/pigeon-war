#ifndef DAMAGE_DEALERS_H
#define DAMAGE_DEALERS_H

#include "core/board.h"
#include "managers/health_manager.h"

namespace damage_dealers
{

int random_damage(size_t damage);

int standard_damage_dealer(const damage_pack& dmg);

};

#endif