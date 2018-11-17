//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILLER_H
#define PIGEONWAR_KILLER_H

#include <abilities/kill.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/killer_instinct.h"

class killer final
{
public:
    static void create(base_entity& entity)
    {
        entity.name = "Killer";

        entity.add<health_field>(40);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<kill>());
        abilities_ptr->add_ability(std::make_shared<killer_instinct>(entity.entity_id));
    }
};

#endif //PIGEONWAR_KILLER_H
