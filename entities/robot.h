//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_ROBO_H
#define PIGEONWAR_ROBO_H

#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"

struct robot final
{
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Robot";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::robot);

        return components;
    }
};

#endif //PIGEONWAR_ROBO_H
