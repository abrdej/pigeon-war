#include "wolf.h"

#include "params.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/basic_melee_attack.h"

entity_definition wolf::create()
{
	entity_definition entity_def(typeid(wolf));
	entity_def.name = "Wilk";
	entity_def.health = 30;
	entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
	entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());
	return entity_def;
}