//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_H
#define PIGEONWAR_SPIDER_H

#include <server/abilities/surroundings.h>
#include <server/abilities/jaw_spider.h>
#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/abilities.h"
#include "server/abilities/spider_web.h"

struct spider final
{
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Spider";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<jaw_spider>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<spider_web>(id));
        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<surroundings>(id));

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::spider);

        return components;
    }
};

#endif //PIGEONWAR_SPIDER_H
