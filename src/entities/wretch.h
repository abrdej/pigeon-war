//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include <abilities/wretch_moving.h>
#include <abilities/vicious_circle.h>
#include <abilities/ball_and_chain.h>
#include "entity.h"
#include "components/damage_taker.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "components/power_field.h"

struct wretch final
{
    static void create(base_entity& entity)
    {
        entity.name = "Wretch";

        entity.add<health_field>(45);
        entity.add<power_filed>(entity.entity_id, 16, 0, 16);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<wretch_moving>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<vicious_circle>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<ball_and_chain>(entity.entity_id));
    }
};

#endif //PIGEONWAR_WRETCH_H
