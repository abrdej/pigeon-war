//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBER_H
#define PIGEONWAR_ABSORBER_H

#include "entity.h"
#include "abilities/abilities.h"
#include <abilities/moveable.h>
#include <abilities/absorption.h>
#include <abilities/power_circle.h>

class absorber final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Absorber";
        entity_health(components).base_health = 50;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<absorption>(id));
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<power_circle>(id));
        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::absorber);

        return components;
    }
};

#endif //PIGEONWAR_ABSORBER_H
