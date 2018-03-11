//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CREATURE_H
#define PIGEONWAR_CREATURE_H

#include <server/abilities/chopper.h>
#include <server/abilities/spiral_of_fire.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class creature final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Fiery Hedgehog";

        entity.add<health_field>(50);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<chopper>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<spiral_of_fire>());

        //entity.add<bitmap_field>(entity.entity_id, "creature);

        return entity;
    }
};

#endif //PIGEONWAR_CREATURE_H
