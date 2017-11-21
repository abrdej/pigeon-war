//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DESTROYER_H
#define PIGEONWAR_DESTROYER_H

#include <abilities/armor.h>
#include <abilities/blow_the_ax.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class destroyer final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(destroyer));
        entity_def.name = "Niszczyciel";
        entity_def.health_pack.base_health = 55;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<blow_the_ax>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<armor>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_DESTROYER_H
