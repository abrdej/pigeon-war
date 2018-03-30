#include "map_reader.h"
#include <external/json.hpp>
#include <fstream>
#include <utils/creator_helper.h>

#include "registered_entities.h"

using nlohmann::json;

using creator_helper::pos;

void create_around_map(const std::string& type_name) {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> trees_positions;
    for (std::int32_t i = 0; i < board::cols_n; ++i) {
        for (std::int32_t j = 0; j < board::rows_n; ++j) {
            if (i == 0 || j == 0 || i == board::cols_n - 1|| j == board::rows_n - 1) {
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

std::string read_map_from_json(const std::string& json_file) {

    try {

        std::ifstream json_stream(json_file);
        auto json_data = json::parse(json_stream);

        try_set_around_map(json_data);

        std::array<std::string, 4> types = {
                "tree", "stone", "fir", "wall"
        };

        for (auto&& type : types) {
            if (json_data.count(type)) {
                std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data[type];
                creator_helper::create_neutral_many(type, positions);
            }
        }
//
//        if (json_data.count("tree")) {
//            std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data["tree"];
//            creator_helper::create_neutral_many<tree>(positions);
//
//        }
//
//        if (json_data.count("stone")) {
//            std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data["stone"];
//            creator_helper::create_neutral_many<stone>(positions);
//
//        }
//
//        if (json_data.count("fir")) {
//            std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data["fir"];
//            creator_helper::create_neutral_many<fir>(positions);
//        }
//
//        if (json_data.count("wall")) {
//            std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = json_data["wall"];
////            creator_helper::create_neutral_many<wall>(positions);
//
//            for (auto& position : positions)
//            {
//                std::uint32_t id = entity_manager::create<wall>();
//                board::insert(board::to_index(position.first, position.second), id);
//                players_manager::add_destructive_surroundings(id);
//            }
//        }

        return json_data["name"];

    } catch (...) {



    }
}