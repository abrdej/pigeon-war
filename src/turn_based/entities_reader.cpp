#include <turn_based/entities_reader.h>

#include <fstream>
#include <iostream>

#include <external/json.hpp>

using nlohmann::json;

std::vector<std::string> read_entities_from_json(const std::string& json_file) {
  std::ifstream json_stream(json_file);
  auto json_data = json::parse(json_stream);
  return json_data["entities"];
}
