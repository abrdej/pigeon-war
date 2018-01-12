//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_MOUSE_H
#define PIGEONWAR_MOUSE_H

#include <server/abilities/poisoned_missile.h>
#include <server/abilities/long_range_missile.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class mouse final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Poisoner";
        entity_health(components).base_health = 35;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<poisoned_missile>());

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::mouse);

        return components;
    }
};

#endif //PIGEONWAR_MOUSE_H
