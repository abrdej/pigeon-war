#include "wolf.h"

#include "params.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/basic_melee_attack.h"

entity_data wolf::create()
{
	entity_data data(typeid(wolf));
	data.name = "Wilk";
	data.health = 30;
	data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
	data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());
	return data;
}