#include <sorcerer.h>

#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <abilities/prison_connection.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void sorcerer::create(base_entity& entity)
{
    entity.name = "Sorcerer";

    entity.add<health_field>(45);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<prison_connection>(entity.entity_id));
}
