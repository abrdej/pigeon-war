//
// Created by abrde on 27.01.2018.
//

#ifndef PIGEONWAR_COMMANDER_H
#define PIGEONWAR_COMMANDER_H

#include "entity.h"
#include "abilities/abilities.h"
#include <abilities/moveable.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <abilities/portal.h>
#include <abilities/cure.h>
#include <abilities/lightning.h>
#include <abilities/arrow.h>
#include <abilities/aura_of_destruction.h>

class commander final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Commander";

        entity.add<health_field>(50);
        entity.add<power_filed>(entity.entity_id, 10, 5, 10);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<arrow>());
        abilities_ptr->add_ability(std::make_shared<aura_of_destruction>(entity.entity_id));

        return entity;
    }
};

#endif //PIGEONWAR_COMMANDER_H
