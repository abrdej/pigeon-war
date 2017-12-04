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
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(robot));
        entity_def.name = "Robot";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        return entity_def;
    }
};

#endif //PIGEONWAR_ROBO_H
