#include "combat_robot.h"
#include "components/damage_taker.h"
#include "components/applied_effects.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/missile_of_doom.h"
#include "abilities/barrier.h"

base_entity combat_robot::create(base_entity& entity)
{
    entity.name = "Combat Robot";

    entity.add<health_field>(50);
    entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<missile_of_doom>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<barrier>(entity.entity_id));

    return entity;
}