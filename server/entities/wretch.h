//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include <server/abilities/wretch_moving.h>
#include <server/abilities/vicious_circle.h>
#include <abilities/ball_and_chain.h>
#include "entity.h"
#include "components/damage_taker.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "components/power_field.h"

struct wretch final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Wretch";

        entity.add<health_field>(45);
        entity.add<power_field>(16);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<wretch_moving>(entity.entity_id));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<vicious_circle>(entity.entity_id));
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<ball_and_chain>(entity.entity_id));

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::wretch);

        return entity;
    }
};

#endif //PIGEONWAR_WRETCH_H
