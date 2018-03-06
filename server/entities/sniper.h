//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_SNIPER_H
#define PIGEONWAR_SNIPER_H

#include <server/abilities/hypnosis.h>
#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/sniper_shot.h"

struct sniper final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Sniper";

        entity.add<health_field>(35);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<sniper_shot>());
        abilities_ptr->add_ability(std::make_shared<hypnosis>());

        //entity.add<bitmap_field>(entity.entity_id, bitmap_key::sniper);

        return entity;
    }
};

#endif //PIGEONWAR_SNIPER_H
