#include <entities/entities_factory.h>

#include <fstream>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include <external/json.hpp>

#include <config.h>
#include <core/game.h>
#include <core/logger.h>
#include <entities/entity_factory_interface.h>
#include <managers/entity_manager.h>

inline std::string get_entity_plugin(const std::string& entity_name) {
  std::ifstream ifs(config_directory + "entity_plugins.json");
  nlohmann::json parsed = nlohmann::json::parse(ifs);
  return parsed[entity_name];
}

std::uint32_t entities_factory::create(const std::string& entity_name) {
  boost::dll::fs::path plugin_path(get_entity_plugin(entity_name));
  boost::dll::shared_library plugin(plugin_path);

  LOG(debug)
    << "Loading entity: " << std::quoted(entity_name) << " from plugin: " << std::quoted(plugin_path.string());

  boost::function<entity_factory_interface_ptr()>
      factory_fn = plugin.get_alias<entity_factory_interface_ptr()>(entity_name);

  return game::get<entity_manager>().create([factory_fn](base_entity& entity) {
    factory_fn()->create(entity);
  });
}
