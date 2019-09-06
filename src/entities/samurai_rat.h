#pragma once

#include <abilities/abilities.h>
#include <abilities/dodge.h>
#include <abilities/moveable.h>
#include <abilities/sword_blow.h>
#include <components/applied_effects.h>
#include <components/modification.h>
#include <entities/entity.h>

struct samurai_rat final {
  static void create(base_entity& entity) {
    entity.name = "Samurai";

    entity.add<health_field>(45);
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<sword_blow>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<dodge>(entity.entity_id));
  }
};
