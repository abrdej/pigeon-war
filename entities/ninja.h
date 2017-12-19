//
// Created by abrde on 12.12.2017.
//

#ifndef PIGEONWAR_NINJA_H
#define PIGEONWAR_NINJA_H

#include <abilities/shiruken.h>
#include <abilities/assassin_slash.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/interception.h"
#include "abilities/assassin_slash.h"

class ninja final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Ninja";
        entity_health(components).base_health = 30;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<shiruken>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<assassin_slash>(id));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::ninja);

        return components;
    }
};

#endif //PIGEONWAR_NINJA_H
