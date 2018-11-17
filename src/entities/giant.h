//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_GIANT_H
#define PIGEONWAR_GIANT_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/aura_of_immunity.h"
#include "abilities/giant_blow.h"
#include "abilities/giant_ram.h"
#include "components/applied_effects.h"

struct giant final
{
    static void create(base_entity& entity)
    {
        entity.name = "Giant";

        entity.add<health_field>(70);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<giant_blow>());
        abilities_ptr->add_ability(std::make_shared<giant_ram>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<aura_of_immunity>(entity.entity_id));
    }
};

#endif //PIGEONWAR_GIANT_H
