#pragma once

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

#include <json.hpp>

template <typename... Args>
std::string string_format(const std::string& format, Args ... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
  if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
  auto size = static_cast<size_t>( size_s );
  auto buf = std::make_unique<char[]>(size);
  std::snprintf(buf.get(), size, format.c_str(), args ...);
  return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
}

inline std::string get_string_from_key(const std::string& config_file, const std::string& name) {
  std::ifstream ifs(config_file);
  try {
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::string description_format = j[name];
    return description_format;
  } catch (std::exception& e) {
    LOG(error) << "Failed to parse json for config file: " << config_file << " and name: " << name;
    throw;
  }
}

class hint_configuration {
 protected:
  template <typename... Args>
  void configure_hint(const std::string& config_file, const std::string& key, Args&... args) {
    hint_format_ = get_string_from_key(config_file, key);
    configurator_ = [this, &args...]() {
      auto hint = string_format(hint_format_, args...);
      return hint;
    };
  }

  [[nodiscard]] std::string get_hint() const {
    return configurator_ ? configurator_() : "Hint configuration not configured yet...";
  }

 private:
  std::string hint_format_;
  std::function<std::string()> configurator_;
};
