#include <entities/entities_factory.h>

#include <fstream>
#include <unordered_map>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include <external/json.hpp>

#include <config.h>
#include <core/game.h>
#include <core/logger.h>
#include <entities/entity_factory_interface.h>
#include <managers/entity_manager.h>

inline std::string get_entity_plugin_path(const std::string& entity_name) {
  std::ifstream ifs(config_directory + "entity_plugins.json");
  nlohmann::json parsed = nlohmann::json::parse(ifs);
  return parsed[entity_name];
}

struct entity_plugin {
  explicit entity_plugin(std::string entity_name) {
    boost::dll::fs::path plugin_path(get_entity_plugin_path(entity_name));
    plugin_ = boost::dll::shared_library(plugin_path);

    LOG(debug)
      << "Loading entity: " << std::quoted(entity_name) << " from plugin: " << std::quoted(plugin_path.string());

    factory_fn_ = plugin_.get_alias<entity_factory_interface_ptr()>(entity_name);
  }

  void create(base_entity& entity) {
    factory_fn_()->create(entity);
  }

  boost::dll::shared_library plugin_;
  boost::function<entity_factory_interface_ptr()> factory_fn_;
};

struct entities_factory::pimpl {
  pimpl() = default;

  std::uint32_t create(const std::string& entity_name) {
    auto it = plugins_.find(entity_name);
    if (it == std::end(plugins_)) {
      it = plugins_.emplace(entity_name, entity_name).first;
    }
    return game::get<entity_manager>().create([it](base_entity& entity) {
      it->second.create(entity);
    });
  }

  std::unordered_map<std::string, entity_plugin> plugins_;
};

entities_factory::entities_factory() : pimpl_(std::make_unique<pimpl>()) {

}

entities_factory::~entities_factory() = default;

std::uint32_t entities_factory::create(const std::string& entity_name) {
  return pimpl_->create(entity_name);
}
