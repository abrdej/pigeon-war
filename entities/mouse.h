//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_MOUSE_H
#define PIGEONWAR_MOUSE_H

#include <abilities/poisoned_missile.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class mouse final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(mouse));
        entity_def.name = "Mysz";
        entity_def.health_pack.base_health = 35;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<poisoned_missile>());
        return entity_def;
    }
};

#endif //PIGEONWAR_MOUSE_H
