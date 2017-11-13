#include "shooter.h"

#include "params.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"

entity_data shooter::create()
{
	entity_data data(typeid(shooter));
	data.name = "Strzelec";
	data.health = 50;
	data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
	data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
	data.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<grenade>());
	return data;
}