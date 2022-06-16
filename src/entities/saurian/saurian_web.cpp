#include <boost/dll/alias.hpp>

#include <components/health_field.h>
#include <entities/entity_factory_interface.h>

struct saurian_web_factory : public entity_factory_interface {
  void create(base_entity& entity) override;
};

void saurian_web_factory::create(base_entity& entity) {
  entity.name = "Saurian Web";

  entity.add<health_field>(20);
}

entity_factory_interface_ptr create_saurian_web_factory() {
  return std::make_shared<saurian_web_factory>();
}

BOOST_DLL_ALIAS(
    create_saurian_web_factory,
    saurian_web
)
