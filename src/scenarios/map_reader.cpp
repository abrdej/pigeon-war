#include "map_reader.h"

#include <fstream>

#include <external/json.hpp>

#include <scenarios/registered_entities.h>
#include <scenarios/creator_helper.h>

using nlohmann::json;

using creator_helper::pos;

void create_around_map(const std::string& type_name) {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> trees_positions;
    for (std::int32_t i = 0; i < game_board().cols_n; ++i) {
        for (std::int32_t j = 0; j < game_board().rows_n; ++j) {
            if (i == 0 || j == 0 || i == game_board().cols_n - 1|| j == game_board().rows_n - 1) {
                trees_positions.push_back(pos(i, j));
            }
        }
    }
    if (type_name == "tree") {
        creator_helper::create_neutral_many<tree>(trees_positions);
    } else if (type_name == "fir") {
        creator_helper::create_neutral_many<fir>(trees_positions);
    } else if (type_name == "stone") {
        creator_helper::create_neutral_many<stone>(trees_positions);
    } else {
        throw std::runtime_error("undefined neutral type");
    }
}

void try_set_around_map(const json& json_data) {
    auto result = json_data.count("around_map");
    if (result != 0) {
        std::string type_name = json_data["around_map"];
        create_around_map(type_name);
    }
}

std::string read_map_from_json(const std::string& json_file, std::pair<uint32_t, uint32_t>& map_size) {

    try {
        std::ifstream json_stream(json_file);
        auto json_data = json::parse(json_stream);

        map_size = json_data["size"];
        game_board().set_size(map_size.first, map_size.second);

        try_set_around_map(json_data);

        std::array<std::string, 5> types = {
                "tree", "stone", "fir", "wall", "fire"
        };

        for (auto&& type : types) {
            if (json_data.count(type)) {
                std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data[type];
                creator_helper::create_neutral_many(type, positions);
            }
        }
        return json_data["name"];

    } catch (...) {

    }
}