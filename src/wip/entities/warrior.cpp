#include <warrior.h>

#include <turn_based/abilities.h>
#include <abilities/immortality.h>
#include <turn_based/move.h>
#include <abilities/warrior_blow.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void warrior::create(base_entity& entity)
{
    entity.name = "Warrior";

    entity.add<health_field>(50);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<warrior_blow>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<immortality>(entity.entity_id));
}
