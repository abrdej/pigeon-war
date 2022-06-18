#include <sentinel.h>

#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <abilities/stamp.h>
#include <abilities/sparks.h>
#include <components/applied_effects.h>
#include <components/modification.h>
#include <components/power_field.h>

void sentinel::create(base_entity& entity) {
  entity.name = "Sentinel";

  entity.add<health_field>(45);
  entity.add<power_filed>(entity.entity_id, 0, 0, 20);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(3));
  abilities_ptr->add_ability(std::make_shared<stamp>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<sparks>(entity.entity_id));
}
