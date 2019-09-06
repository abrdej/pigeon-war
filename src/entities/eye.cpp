#include <entities/eye.h>

#include <abilities/abilities.h>
#include <abilities/eye_shoot.h>
#include <abilities/moveable.h>
#include <abilities/transmission.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void eye::create(base_entity& entity) {
    entity.name = "Eye";

    entity.add<health_field>(45);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<eye_shoot>());
    abilities_ptr->add_ability(std::make_shared<transmission>(entity.entity_id));
}
