//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_H
#define PIGEONWAR_SPIDER_H

#include <abilities/surroundings.h>
#include <abilities/jaw_spider.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/spider_web.h"

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

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::spider);

        return components;
    }
};

#endif //PIGEONWAR_SPIDER_H
