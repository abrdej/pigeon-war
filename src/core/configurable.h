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

  [[nodiscard]] const std::string& get_name() const {
    return name_;
  }

  template <class T>
  void get_param(const std::string& name, T& value) {
    value = parsed_[name];
  }

  template <class T>
  T get_param(const std::string& name) {
    return parsed_[name];
  }

 private:
  std::string name_;
  nlohmann::json parsed_;
};
