#pragma once

#include <fstream>
#include <string>

#include <external/json.hpp>

#include <config.h>

class configurable {
 public:
  explicit configurable(std::string name) {
    name_ = std::move(name);
    std::ifstream ifs(config_directory + get_name() + ".json");
    parsed_ = nlohmann::json::parse(ifs);
  }

  explicit configurable(const std::string& custom_config_directory, std::string name) {
    name_ = std::move(name);
    std::ifstream ifs(custom_config_directory + get_name() + ".json");
    parsed_ = nlohmann::json::parse(ifs);
  }

  [[nodiscard]] const std::string& get_name() const {
    return name_;
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
  std::string name_;
  nlohmann::json parsed_;
};
