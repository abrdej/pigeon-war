//
// Created by abrde on 20.01.2018.
//

#ifndef PIGEONWAR_SOUL_HUNTER_H
#define PIGEONWAR_SOUL_HUNTER_H

#include <abilities/prison_connection.h>
#include <components/damage_taker.h>
#include <components/additions.h>
#include <abilities/suck_the_soul.h>
#include "entity.h"
#include "server/abilities/moveable.h"

struct soul_hunter final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Soul Hunter";

        entity.add<health_field>(50);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<suck_the_soul>(entity.entity_id));

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::soul_hunter);

        return entity;
    }
};


#endif //PIGEONWAR_SOUL_HUNTER_H
