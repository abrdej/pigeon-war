//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILLER_H
#define PIGEONWAR_KILLER_H

#include <abilities/kill.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/killer_instinct.h"

class killer final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Killer";
        entity_health(components).base_health = 40;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<kill>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<killer_instinct>(id));
        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::killer);

        return components;
    }
};

#endif //PIGEONWAR_KILLER_H
