//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DESTROYER_H
#define PIGEONWAR_DESTROYER_H

#include <abilities/armor.h>
#include <abilities/blow_the_ax.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class destroyer final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Destroyer";
        entity_health(components).base_health = 50;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<blow_the_ax>());
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<armor>(id));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::destroyer);

        return components;
    }
};

#endif //PIGEONWAR_DESTROYER_H
