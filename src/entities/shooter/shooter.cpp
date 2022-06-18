#include <boost/dll/alias.hpp>

#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/entity_factory_interface.h>
#include <grenade.h>
#include <shoot.h>

#include <turn_based/game.h>
#include <turn_based/board.h>

struct shooter_factory : public entity_factory_interface {
  void create(base_entity& entity) override;
};

void shooter_factory::create(base_entity& entity) {
  entity.name = "Shooter";

  LOG(debug) << "shooter_factory size: " << game_board().cols_n * game_board().rows_n;

  entity.add<health_field>(50);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<shoot>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<grenade>(entity.entity_id));
}

entity_factory_interface_ptr create_shooter_factory() {
  return std::make_shared<shooter_factory>();
}

BOOST_DLL_ALIAS(create_shooter_factory, shooter)
