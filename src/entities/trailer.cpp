#include <trailer.h>

#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <abilities/talons.h>
#include <abilities/trash_trail.h>
#include <components/applied_effects.h>

void trailer::create(base_entity& entity) {
  entity.name = "Trailer";

  entity.add<health_field>(40);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<talons>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<trash_trail>(entity.entity_id));
}
