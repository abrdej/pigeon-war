//
// Created by abrde on 28.01.2018.
//

#ifndef PIGEONWAR_GIN_H
#define PIGEONWAR_GIN_H

#include <abilities/uselessness.h>
#include <turn_based/entity.h>
#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <abilities/fist_of_doom.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

struct gin final
{
    static void create(base_entity& entity)
    {
        entity.name = "Gin";

        entity.add<health_field>(45);
        entity.add<power_filed>(entity.entity_id, 0, 1);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<fist_of_doom>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<uselessness>(entity.entity_id));
    }
};

#endif //PIGEONWAR_GIN_H
