//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_GRENADIER_H
#define PIGEONWAR_GRENADIER_H

#include <abilities/poisoned_missile.h>
#include <abilities/bomb.h>
#include <abilities/detonation.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class grenadier final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Grenadier";
        entity_health(components).base_health = 40;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<bomb>());
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<detonation>(id));
        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::grenadier);
        return components;
    }
};

#endif //PIGEONWAR_GRENADIER_H
