#include <reaper.h>

#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <abilities/charge.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>

void reaper::create(base_entity& entity) {
    entity.name = "Reaper";

    entity.add<health_field>(45);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<charge>(entity.entity_id));
}
