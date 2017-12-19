//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MONK_H
#define PIGEONWAR_MONK_H

#include <abilities/magic_bullet.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class monk final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(monk));
        entity_def.name = "Monk";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<magic_bullet>(id));

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::monk);

        return entity_def;
    }
};

#endif //PIGEONWAR_MONK_H
