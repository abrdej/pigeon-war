//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_WARRIOR_H
#define PIGEONWAR_WARRIOR_H

#include <abilities/warrior_blow.h>
#include <abilities/immortality.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class warrior final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Warrior";
        entity_health(components).base_health = 50;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<warrior_blow>());
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<immortality>(id));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::warrior);

        return components;
    }
};

#endif //PIGEONWAR_WARRIOR_H
