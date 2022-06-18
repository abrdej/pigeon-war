#pragma once

#include <external/json.hpp>

#include <turn_based/logger.h>

class message_processor {
 public:
  using json_data_type = nlohmann::json;
  using callback_type = std::function<void(json_data_type&)>;

  void bind(const std::string& message_type, callback_type callback);
  void execute(const std::string& message);

 private:
  void execute(json_data_type data);

  std::unordered_map<std::string, callback_type> callbacks_;
};
