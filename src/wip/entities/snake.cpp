#include <snake.h>

#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <abilities/fast_draw.h>
#include <abilities/revolver.h>
#include <abilities/smokescreen.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void snake::create(base_entity& entity) {
  entity.name = "Snake";

  entity.add<health_field>(45);
  // entity.add<damage_taker>();
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<revolver>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<fast_draw>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<smokescreen>(entity.entity_id));
}
