//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_SORCERER_H
#define PIGEONWAR_SORCERER_H

#include "entity.h"
#include "server/abilities/moveable.h"

struct sorcerer final
{
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Sorcerer";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::sorcerer);

        return components;
    }
};

#endif //PIGEONWAR_SORCERER_H
