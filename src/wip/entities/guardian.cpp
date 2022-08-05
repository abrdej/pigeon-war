#include <guardian.h>

#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <abilities/shield.h>
#include <abilities/spear.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/modification.h>

void guardian::create(base_entity& entity) {
  entity.name = "Guardian";

  entity.add<health_field>(65);
  // entity.add<damage_taker>();
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<spear>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<shield>(entity.entity_id));
}
