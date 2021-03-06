#include "native.h"

#include <abilities/abilities.h>
#include <abilities/counterattack.h>
#include <abilities/drain.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void native::create(base_entity& entity) {
    entity.name = "Native";

    entity.add<health_field>(50);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<drain>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<counterattack>(entity.entity_id));
}