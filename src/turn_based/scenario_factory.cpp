#include <turn_based/scenario_factory.h>

#include <fstream>
#include <unordered_map>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include <external/json.hpp>

#include <config.h>
#include <turn_based/logger.h>
#include <turn_based/scenario_factory_interface.h>

inline std::string get_scenario_plugin_path(const std::string& scenario_name) {
  std::ifstream ifs(config_directory + "scenario_plugins.json");
  try {
    nlohmann::json parsed = nlohmann::json::parse(ifs);
    return parsed[scenario_name];
  } catch (std::exception& e) {
    LOG(error) << "no scenario plugin for: " << std::quoted(scenario_name) << ", what: " << e.what();
  }
  return {};
}

struct scenario_plugin {
  explicit scenario_plugin(std::string scenario_name) {
    boost::dll::fs::path plugin_path(get_scenario_plugin_path(scenario_name));
    plugin_ = boost::dll::shared_library(plugin_path);

    LOG(debug)
      << "Loading scenario: " << std::quoted(scenario_name) << " from plugin: " << std::quoted(plugin_path.string());

    factory_fn_ = plugin_.get_alias<scenario_factory_interface_ptr()>(scenario_name);
  }

  void create() {
    factory_fn_()->create();
  }

  boost::dll::shared_library plugin_;
  boost::function<scenario_factory_interface_ptr()> factory_fn_;
};

struct scenario_factory::pimpl {
  pimpl() = default;

  void create(const std::string& scenario_name) {
    auto it = plugins_.find(scenario_name);
    if (it == std::end(plugins_)) {
      it = plugins_.emplace(scenario_name, scenario_name).first;
    }
    it->second.create();
  }

  std::unordered_map<std::string, scenario_plugin> plugins_;
};

scenario_factory::scenario_factory() : pimpl_(std::make_unique<pimpl>()) {

}

scenario_factory::~scenario_factory() = default;

void scenario_factory::create(const std::string& scenario_name) {
  pimpl_->create(scenario_name);
}
