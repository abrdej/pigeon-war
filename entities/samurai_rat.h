//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SAMURAI_RAT_H
#define PIGEONWAR_SAMURAI_RAT_H

#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/sword_blow.h"


struct samurai_rat final
{
    static entity_data create() {
        entity_data data(typeid(samurai_rat));
        data.name = "Samuraj";
        data.health = 45;
        data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<sword_blow>());
        return data;
    }
};

#endif //PIGEONWAR_SAMURAI_RAT_H
