#pragma once

#include <fstream>
#include <string>

#include <json.hpp>

#include <config.h>
#include <logging/logger.h>

class configurable {
 public:
  configurable() = default;

  explicit configurable(const std::string& name) {
    try {
      std::ifstream ifs(config_directory + name + ".json");
      parsed_ = nlohmann::json::parse(ifs);
    } catch (std::exception& e) {
      LOG(error) << "Failed to parse json file: " << config_directory + name + ".json";
      throw;
    }
  }

  configurable(const std::string& custom_config_directory, const std::string& name) {
    std::ifstream ifs(custom_config_directory + name + ".json");
    if (ifs.is_open()) {
      LOG(debug) << "loading configuration from: " << custom_config_directory + name + ".json";
      try {
        parsed_ = nlohmann::json::parse(ifs);
      } catch (std::exception& e) {
        LOG(error) << "Failed to parse json file: " << config_directory + name + ".json";
        throw;
      }
    }
  }

  configurable(const std::string& name, bool) {
    initialize(name);
  }

  void initialize(const std::string& name) {
    std::ifstream ifs(config_directory + name + ".json");
    if (ifs.is_open()) {
      LOG(debug) << "loading configuration from: " << config_directory + name + ".json";
      try {
        parsed_ = nlohmann::json::parse(ifs);
      } catch (std::exception& e) {
        LOG(error) << "Failed to parse json file: " << config_directory + name + ".json";
        throw;
      }
    }
  }

  template <typename T>
  void get_param(const std::string& name, T& value) {
    value = parsed_[name];
  }

  template <typename T>
  T get_param(const std::string& name) {
    return parsed_[name];
  }

  template <typename T>
  T get_param_or_default(const std::string& name, const T& default_value) {
    auto it = parsed_.find(name);
    return it != std::end(parsed_) ? static_cast<T>(*it) : default_value;
  }

 private:
  nlohmann::json parsed_;
};
