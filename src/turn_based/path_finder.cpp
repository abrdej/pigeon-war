#include <turn_based/path_finder.h>

#include <turn_based/board.h>
#include <logging/logger.h>

// TODO: we can use board_container to fill this
path_finder::path_finder(bool all_fields) : start_index_(-1) {
  board_graph.set_size(game_board().cols_n * game_board().rows_n);

  game_board().for_each(
      [this, &all_fields](entity_id_t entity_id, std::uint32_t col, std::uint32_t row) {
        auto rows_n = game_board().rows_n;
        auto cols_n = game_board().cols_n;
        auto key_from = game_board().to_index(col, row);

        if (row < rows_n - 1) {
          auto key_to = game_board().to_index(col, row + 1);
          if (game_board().empty(key_to) || all_fields) board_graph.add_edge(key_from.cast(), key_to.cast());

          if (game_board().empty(key_from) || all_fields) board_graph.add_edge(key_to.cast(), key_from.cast());
        }
        if (col < cols_n - 1) {
          auto key_to = game_board().to_index(col + 1, row);
          if (game_board().empty(key_to) || all_fields) board_graph.add_edge(key_from.cast(), key_to.cast());

          if (game_board().empty(key_from) || all_fields) board_graph.add_edge(key_to.cast(), key_from.cast());
        }
      });
}

void path_finder::calc(index_t from_index) {
  start_index_ = from_index;
  distance_map_.clear();
  sequence_map_.clear();

  std::vector<graph::vertex_descriptor> sequence_map;
  breadth_search(board_graph, from_index.cast(), distance_map_, sequence_map);
  for (auto index : sequence_map) {
    sequence_map_.emplace_back(index_t{index});
  }
}

index_t path_finder::find_first_satisfy_conditions(
    index_t from_index, const std::function<bool(index_t)>& condition) {
  start_index_ = from_index;
  distance_map_.clear();
  sequence_map_.clear();

  std::vector<graph::vertex_descriptor> sequence_map;
  auto result = breadth_search(board_graph, from_index.cast(), distance_map_, sequence_map,
                               [condition](graph::vertex_descriptor index) {
                                  return condition(index_t{index});
                               });
  for (auto index : sequence_map) {
    sequence_map_.emplace_back(index_t{index});
  }
  return index_t{result};
}

void path_finder::get_possible_movements(std::vector<index_t>& movements,
                                         std::vector<std::uint32_t>& costs, std::int32_t range) {
  movements.clear();
  costs.clear();
  for (std::size_t i = 0; i < distance_map_.size(); ++i)
    if (distance_map_[i] <= range && distance_map_[i] != 0) {
      movements.emplace_back(i);
      costs.emplace_back(distance_map_[i]);
    }
}

void path_finder::path_to(index_t index, std::vector<index_t>& path) {
  if (sequence_map_.empty()) return;
  auto path_index = index;
  path.push_back(index);
  int i = 0;
  while (path_index != start_index_ && i++ != 100) {
    path_index = sequence_map_[path_index.cast()];
    path.push_back(path_index);

    LOG(debug) << "start_index_: " << path_index;
    LOG(debug) << "path_index: " << path_index;
  }
}

std::int32_t path_finder::distance_to(index_t index) {
  return static_cast<std::int32_t>(distance_map_[index.cast()]);
}
