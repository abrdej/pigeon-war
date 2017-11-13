#include "shooter.h"

#include "params.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"

entity_definition shooter::create()
{
	entity_definition entity_def(typeid(shooter));
	entity_def.name = "Strzelec";
	entity_def.health = 50;
	entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
	entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
	entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<grenade>());
	return entity_def;
}