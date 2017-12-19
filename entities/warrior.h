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
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(warrior));
        entity_def.name = "Wojownik";
        entity_def.health_pack.base_health = 50;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<warrior_blow>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<immortality>(id));

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::warrior);

        return entity_def;
    }
};

#endif //PIGEONWAR_WARRIOR_H
