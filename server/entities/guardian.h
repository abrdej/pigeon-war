//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_GUARDIAN_H
#define PIGEONWAR_GUARDIAN_H

#include <server/abilities/spear.h>
#include <server/abilities/shield.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class guardian final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Guardian";
        entity_health(components).base_health = 65;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<spear>(id));
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<shield>(id));

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::guardian);

        return components;
    }
};

#endif //PIGEONWAR_GUARDIAN_H
