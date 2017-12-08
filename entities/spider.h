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
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(spider));
        entity_def.name = "Pająk";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<jaw_spider>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<spider_web>(id));
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<surroundings>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_SPIDER_H
