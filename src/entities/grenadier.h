//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_GRENADIER_H
#define PIGEONWAR_GRENADIER_H

#include <abilities/poisoned_missile.h>
#include <abilities/bomb.h>
#include <abilities/detonation.h>
#include <components/modification.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class grenadier final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Grenadier";

        entity.add<health_field>(40);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<bomb>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<detonation>(entity.entity_id));

        return entity;
    }
};

#endif //PIGEONWAR_GRENADIER_H
