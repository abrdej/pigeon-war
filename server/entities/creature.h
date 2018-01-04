//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CREATURE_H
#define PIGEONWAR_CREATURE_H

#include <server/abilities/chopper.h>
#include <server/abilities/spiral_of_fire.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class creature final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Fiery Hedgehog";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<chopper>(id));
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<spiral_of_fire>());

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::creature);

        return components;
    }
};

#endif //PIGEONWAR_CREATURE_H