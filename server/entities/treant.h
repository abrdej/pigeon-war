//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_TREANT_H
#define PIGEONWAR_TREANT_H

#include "entity.h"
#include <server/abilities/entangling.h>
#include <server/abilities/recovery.h>
#include "server/abilities/moveable.h"


struct treant final
{
    static auto create(base_entity& entity)
    {
            entity.name = "Treant";

            entity.add<health_field>(55);
            entity.add<damage_taker>();

            auto abilities_ptr = entity.add<abilities>();
            abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(2));
//            abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<entangling>(entity.entity_id));
//            abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<recovery>(entity.entity_id));
            entity.add<bitmap_field>(entity.entity_id, bitmap_key::treant);

            return entity;
    }
};

#endif //PIGEONWAR_TREANT_H
