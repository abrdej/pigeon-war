#include <turn_based/ai_factory.h>

#include <fstream>
#include <unordered_map>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include <external/json.hpp>

#include <config.h>
#include <turn_based/logger.h>
#include <turn_based/ai_factory_interface.h>

inline std::string get_ai_plugin_path(const std::string& ai_name) {
  std::ifstream ifs(config_directory + "ai_plugins.json");
  try {
    nlohmann::json parsed = nlohmann::json::parse(ifs);
    return parsed[ai_name];
  } catch (std::exception& e) {
    LOG(error) << "no ai plugin for: " << std::quoted(ai_name) << ", what: " << e.what();
  }
  return {};
}

struct ai_plugin {
  explicit ai_plugin(std::string ai_name) {
    boost::dll::fs::path plugin_path(get_ai_plugin_path(ai_name));
    plugin_ = boost::dll::shared_library(plugin_path);

    LOG(debug)
      << "Loading ai: " << std::quoted(ai_name) << " from plugin: " << std::quoted(plugin_path.string());

    factory_fn_ = plugin_.get_alias<ai_factory_interface_ptr()>(ai_name);
  }

  ai::behavior_node_ptr create() {
    return factory_fn_()->create();
  }

  boost::dll::shared_library plugin_;
  boost::function<ai_factory_interface_ptr()> factory_fn_;
};

struct ai_factory::pimpl {
  pimpl() = default;

  ai::behavior_node_ptr create(const std::string& ai_name) {
    auto it = plugins_.find(ai_name);
    if (it == std::end(plugins_)) {
      it = plugins_.emplace(ai_name, ai_name).first;
    }
    return it->second.create();
  }

  std::unordered_map<std::string, ai_plugin> plugins_;
};

ai_factory::ai_factory() : pimpl_(std::make_unique<pimpl>()) {

}

ai_factory::~ai_factory() = default;

ai::behavior_node_ptr ai_factory::create(const std::string& ai_name) {
  return pimpl_->create(ai_name);
}
