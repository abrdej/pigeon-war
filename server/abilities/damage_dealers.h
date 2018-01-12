#ifndef DAMAGE_DEALERS_H
#define DAMAGE_DEALERS_H

#include "core/board.h"
#include "managers/health_manager.h"

namespace damage_dealers
{

sf::Int32 random_damage(sf::Uint64 damage);

sf::Int32 standard_damage_dealer(const damage_pack& dmg);

};

#endif