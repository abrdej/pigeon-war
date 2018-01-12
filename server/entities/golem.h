//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GOLEM_H
#define PIGEONWAR_GOLEM_H

#include <abilities/stone_skin.h>
#include <abilities/power_bullet.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/defender.h"
#include "abilities/giant_blow.h"
#include "abilities/giant_ram.h"

struct golem final
{
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Golem";
        entity_health(components).base_health = 60;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<power_bullet>());
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<stone_skin>(id));
        entity_directions(components) = directions::left;
        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::golem);

        return components;
    }
};


#endif //PIGEONWAR_GOLEM_H
