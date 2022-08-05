//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CREATURE_H
#define PIGEONWAR_CREATURE_H

#include <abilities/chopper.h>
#include <abilities/spiral_of_fire.h>
#include <components/applied_effects.h>
#include <components/modification.h>
#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <turn_based/entity.h>

class creature final {
 public:
  static void create(base_entity& entity) {
    entity.name = "Fiery Hedgehog";

    entity.add<health_field>(50);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<chopper>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<spiral_of_fire>());
  }
};

#endif  // PIGEONWAR_CREATURE_H
