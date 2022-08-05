#include <poisoner.h>

#include <turn_based/abilities.h>
#include <abilities/long_range_missile.h>
#include <turn_based/move.h>
#include <abilities/poisoned_missile.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void poisoner::create(base_entity& entity) {
  entity.name = "Poisoner";

  entity.add<health_field>(35);
  // entity.add<damage_taker>();
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(3));
  abilities_ptr->add_ability(std::make_shared<poisoned_missile>(entity.entity_id));
}
