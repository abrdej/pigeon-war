#include <entities/entities_factory.h>
#include <managers/entity_manager.h>
#include <core/game.h>

#include <fstream>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <config.h>
#include <external/json.hpp>
#include <entities/entity_factory_interface.h>

inline std::string get_entity_plugin_path(const std::string& entity_name) {
  std::ifstream ifs(config_directory + "entity_plugins.json");
  nlohmann::json parsed = nlohmann::json::parse(ifs);
  return parsed[entity_name];
}

int main(int argc, char** argv) {
  entities_factory factory;
  auto shooter_id = factory.create("shooter");
  auto saberhand_id = factory.create("saberhand");

  (void)shooter_id;
  (void)saberhand_id;

  game::get<entity_manager>().clear();

  std::cout << "Here\n";

  return 0;
}
