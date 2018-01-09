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

struct giant final
{
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Giant";
        entity_health(components).base_health = 70;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<giant_blow>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<giant_ram>(id));
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<aura_of_immunity>(id));
        entity_directions(components) = directions::left;
        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::giant);

        return components;
    }
};

#endif //PIGEONWAR_GIANT_H
