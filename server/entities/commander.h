//
// Created by abrde on 27.01.2018.
//

#ifndef PIGEONWAR_COMMANDER_H
#define PIGEONWAR_COMMANDER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include <server/abilities/moveable.h>
#include <components/damage_taker.h>
#include <components/additions.h>
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
        entity.add<power_filed_with_charging>(entity.entity_id, 10, 5, 10);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<arrow>());
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<aura_of_destruction>(entity.entity_id));

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::commander);

        return entity;
    }
};

#endif //PIGEONWAR_COMMANDER_H
