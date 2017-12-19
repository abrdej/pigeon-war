//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_TREANT_H
#define PIGEONWAR_TREANT_H

#include <abilities/entangling.h>
#include <abilities/recovery.h>
#include "entity.h"
#include "abilities/moveable.h"


struct treant final
{
    static auto create(size_t id) {

        base_components components;
        entity_name(components) = "Treant";
        entity_health(components).base_health = 55;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(2));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<entangling>(id));
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<recovery>(id));
        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::treant);

        return components;
    }
};

#endif //PIGEONWAR_TREANT_H
