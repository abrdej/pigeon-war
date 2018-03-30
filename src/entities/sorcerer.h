//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_SORCERER_H
#define PIGEONWAR_SORCERER_H

#include <abilities/prison_connection.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <abilities/abilities.h>
#include "entity.h"
#include "abilities/moveable.h"

struct sorcerer final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Sorcerer";

        entity.add<health_field>(45);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<prison_connection>(entity.entity_id));

        //entity.add<bitmap_field>(entity.entity_id, "sorcerer);

        return entity;
    }
};

#endif //PIGEONWAR_SORCERER_H
