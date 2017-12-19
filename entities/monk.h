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
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Monk";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<magic_bullet>(id));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::monk);

        return components;
    }
};

#endif //PIGEONWAR_MONK_H
