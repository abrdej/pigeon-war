#include <boost/dll/alias.hpp>

#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <abilities/smokescreen.h>
#include <components/applied_effects.h>
#include <entities/entity_factory_interface.h>
#include <entities/shooter/grenade.h>
#include <entities/shooter/shoot.h>

#include <core/game.h>
#include <core/board.h>

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
