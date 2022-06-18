#include <boost/dll/alias.hpp>

#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_interface.h>
#include <tongue_of_fire.h>

struct saurian_factory : public entity_factory_interface {
  void create(base_entity& entity) override;
};

void saurian_factory::create(base_entity& entity) {
  entity.name = "Saurian";

  entity.add<health_field>(35);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<tongue_of_fire>(entity.entity_id));
}

entity_factory_interface_ptr create_saurian_factory() {
  return std::make_shared<saurian_factory>();
}

BOOST_DLL_ALIAS(create_saurian_factory, saurian)
