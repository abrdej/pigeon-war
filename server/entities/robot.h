//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_ROBO_H
#define PIGEONWAR_ROBO_H

#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/abilities.h"
#include "server/abilities/shoot.h"
#include "server/abilities/grenade.h"

struct robot final
{
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Robot";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::robot);

        return components;
    }
};

#endif //PIGEONWAR_ROBO_H
