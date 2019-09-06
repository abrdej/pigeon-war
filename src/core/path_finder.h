#pragma once

#include <functional>
#include <unordered_map>

#include <core/defs.h>
#include <utils/graph.h>

class path_finder {
 public:
  explicit path_finder(bool all_fields = false);
  void calc(index_t from_index);

  index_t find_first_satisfy_conditions(index_t from_index,
                                        const std::function<bool(index_t)>& condition);

  void get_possible_movements(std::vector<index_t>& movements,
                              std::vector<std::uint32_t>& costs, std::int32_t range);

  std::int32_t distance_to(index_t index);
  void path_to(index_t index, std::vector<index_t>& path);

 private:
  graph board_graph;
  std::vector<std::int32_t> distance_map_;
  std::vector<index_t> sequence_map_;
  index_t start_index_;
};

namespace board_helper {

void calc_straight(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void calc_diagonal(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void calc_directed(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void neighboring_fields(index_t for_index, std::vector<index_t>& fields,
                        bool available);

void circle(index_t for_index, std::vector<index_t>& fields, bool available);

void all_free(std::vector<index_t>& fields);

void all(std::vector<index_t>& fields);

}  // namespace board_helper
