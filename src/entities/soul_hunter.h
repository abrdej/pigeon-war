//
// Created by abrde on 20.01.2018.
//

#ifndef PIGEONWAR_SOUL_HUNTER_H
#define PIGEONWAR_SOUL_HUNTER_H

#include <abilities/prison_connection.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <abilities/suck_the_soul.h>
#include "entity.h"
#include "abilities/moveable.h"

struct soul_hunter final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Soul Hunter";

        entity.add<health_field>(50);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<suck_the_soul>(entity.entity_id));

        //entity.add<bitmap_field>(entity.entity_id, "soul_hunter);


    }
};


#endif //PIGEONWAR_SOUL_HUNTER_H
