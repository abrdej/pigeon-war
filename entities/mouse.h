//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_MOUSE_H
#define PIGEONWAR_MOUSE_H

#include <abilities/poisoned_missile.h>
#include <abilities/long_range_missile.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class mouse final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Poisoner";
        entity_health(components).base_health = 35;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<poisoned_missile>());

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::mouse);

        return components;
    }
};

#endif //PIGEONWAR_MOUSE_H
