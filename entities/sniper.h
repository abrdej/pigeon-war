//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_SNIPER_H
#define PIGEONWAR_SNIPER_H

#include <abilities/hypnosis.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/sniper_shot.h"

struct sniper final
{
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Sniper";
        entity_health(components).base_health = 35;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<sniper_shot>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<hypnosis>());

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::sniper);

        return components;
    }
};

#endif //PIGEONWAR_SNIPER_H
