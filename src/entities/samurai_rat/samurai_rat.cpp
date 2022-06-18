#include <dodge.h>
#include <sword_blow.h>
#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/moveable.h>

DEFINE_ENTITY_FACTORY(samurai_rat) {
  entity.name = "Samurai";

  entity.add<health_field>(60);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<sword_blow>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<dodge>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(samurai_rat)
