#include "wolf.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/basic_melee_attack.h"

entity_definition wolf::create(size_t id)
{
	entity_definition entity_def(typeid(wolf));
	entity_def.name = "Wilk";
	entity_def.health_pack.base_health = 30;
	entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
	entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());
	return entity_def;
}