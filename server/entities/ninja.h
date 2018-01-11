//
// Created by abrde on 12.12.2017.
//

#ifndef PIGEONWAR_NINJA_H
#define PIGEONWAR_NINJA_H

#include <server/abilities/shiruken.h>
#include <server/abilities/death_mark.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class ninja final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Ninja";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<shiruken>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<death_mark>(id));

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::ninja);

        return components;
    }
};

#endif //PIGEONWAR_NINJA_H
