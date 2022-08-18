#pragma once

#include <functional>

#include <turn_based/defs.h>
#include <turn_based/utils/graph.h>

/**
 * @brief Class used to calculate path finding related outcomes.
 */
class path_finder {
 public:
  explicit path_finder(bool all_fields = false);
  void calc(index_t from_index);

  index_t find_first_satisfy_conditions(index_t from_index, const std::function<bool(index_t)>& condition);

  void get_possible_movements(std::vector<index_t>& movements, std::vector<std::uint32_t>& costs, std::int32_t range);

  std::int32_t distance_to(index_t index);
  void path_to(index_t index, std::vector<index_t>& path);

 private:
  graph board_graph;
  std::vector<std::int32_t> distance_map_;
  std::vector<index_t> sequence_map_;
  index_t start_index_;
};
