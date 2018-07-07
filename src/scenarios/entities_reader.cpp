#include <iostream>
#include <fstream>
#include <external/json.hpp>
#include "entities_reader.h"

using nlohmann::json;

std::vector<std::string> read_entities_from_json(const std::string& json_file) {
    try {
        std::ifstream json_stream(json_file);
        auto json_data = json::parse(json_stream);
        return json_data["entities"];

    } catch (std::exception& e) {
        std::cerr << e.what();
    }
}