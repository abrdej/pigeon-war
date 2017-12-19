//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include <abilities/wretch_moving.h>
#include <abilities/vicious_circle.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "managers/power_manager.h"

struct wretch final
{
    static auto create(size_t id)
    {
        using components_type = std::tuple<name_field, health_field, abilities, directions, drawable::ptr_type, power_field>;

        components_type components;
        entity_name(components) = "Wretch";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<wretch_moving>(id));
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<vicious_circle>(id));
        entity_directions(components) = directions::left;
        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::wretch);
        entity_power(components).base_power = 20;

        return components;
    }
};

#endif //PIGEONWAR_WRETCH_H
