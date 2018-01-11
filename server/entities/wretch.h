//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include <server/abilities/wretch_moving.h>
#include <server/abilities/vicious_circle.h>
#include <abilities/ball_and_chain.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/managers/power_manager.h"

struct wretch final
{
    static auto create(size_t id)
    {
        using components_type = std::tuple<name_field, health_field, abilities, directions, bitmap_field, power_field>;

        components_type components;
        entity_name(components) = "Wretch";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<wretch_moving>(id));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<vicious_circle>(id));
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<ball_and_chain>(id));
        entity_directions(components) = directions::left;
        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::wretch);
        entity_power(components).base_power = 16;

        return components;
    }
};

#endif //PIGEONWAR_WRETCH_H
