//
// Created by abrdej on 24.01.18.
//

#ifndef PIGEONWAR_MECHANICAL_SAW_H
#define PIGEONWAR_MECHANICAL_SAW_H

#include <abilities/saw_passing.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "components/damage_taker.h"
#include "components/additions.h"


class mechanical_saw final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Mechanical Saw";

        entity.add<health_field>(65);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<saw_passing>(entity.entity_id));


        entity.add<bitmap_field>(entity.entity_id, bitmap_key::mechanical_saw);

        return entity;
    }
};

#endif //PIGEONWAR_MECHANICAL_SAW_H
