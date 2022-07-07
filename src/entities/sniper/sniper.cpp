#include <hypnosis.h>
#include <sniper_shot.h>
#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/moveable.h>

DEFINE_ENTITY_FACTORY(sniper) {
  entity.name = "Sniper";

  entity.add<health_field>(35);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(3));
  abilities_ptr->add_ability(std::make_shared<sniper_shot>());
  abilities_ptr->add_ability(std::make_shared<hypnosis>());
}

FACTORY_PLUGIN_ALIAS(sniper)
