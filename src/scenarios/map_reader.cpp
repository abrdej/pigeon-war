#include <scenarios/map_reader.h>

#include <cassert>
#include <fstream>

#include <external/json.hpp>

#include <entities/all_entities.h>
#include <scenarios/creator_helper.h>

using nlohmann::json;

using creator_helper::pos;
using creator_helper::pos_type;

void create_around_map(const std::string& object) {
  assert(game_board().cols_n > 2);
  assert(game_board().rows_n > 2);

  std::vector<pos_type> positions;

  for (std::uint32_t i = 0; i < game_board().cols_n; ++i) {
    positions.push_back(pos(i, 0));
    positions.push_back(pos(i, game_board().rows_n - 1));
  }
  for (std::uint32_t i = 1; i < game_board().rows_n - 1; ++i) {
    positions.push_back(pos(0, i));
    positions.push_back(pos(game_board().cols_n - 1, i));
  }
  creator_helper::create_neutral_many(object, positions);
}

void handle_around_map(const json& json_data) {
  auto result = json_data.count("around_map");
  if (result != 0) {
    const std::string type_name = json_data["around_map"];
    create_around_map(type_name);
  }
}

std::string read_map_from_json(const std::string& json_file,
                               std::pair<uint32_t, uint32_t>& map_size) {
  std::ifstream json_stream(json_file);
  auto json_data = json::parse(json_stream);

  // TODO: probably we don't want to set map size in such a way (if any)
  map_size = json_data["size"];
  game_board().set_size(map_size.first, map_size.second);

  handle_around_map(json_data);

  std::array<std::string, 6> objects = {"tree", "stone", "fir", "wall", "fire", "water"};

  for (const auto& object : objects) {
    if (json_data.count(object)) {
      std::vector<pos_type> positions = json_data[object];
      creator_helper::create_neutral_many(object, positions);
    }
  }
  return json_data["name"];
}
