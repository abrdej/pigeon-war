#include <dragon.h>

#include <turn_based/abilities.h>
#include <abilities/dragon_skin.h>
#include <abilities/flame_burning.h>
#include <turn_based/move.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void dragon::create(base_entity& entity) {
    entity.name = "Dragon";

    entity.add<health_field>(45);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<flame_burning>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<dragon_skin>(entity.entity_id));
}
