#include <commander.h>

#include <turn_based/abilities.h>
#include <abilities/arrow.h>
#include <abilities/aura_of_destruction.h>
#include <turn_based/move.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/power_field.h>

void commander::create(base_entity& entity)
{
    entity.name = "Commander";

    entity.add<health_field>(50);
    entity.add<power_filed>(entity.entity_id, 10, 5, 10);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<arrow>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<aura_of_destruction>(entity.entity_id));
}
