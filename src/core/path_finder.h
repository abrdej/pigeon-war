#pragma once

#include <functional>
#include <unordered_map>

#include <utils/graph.h>

class path_finder {
 public:
  explicit path_finder(bool all_fields = false);
  void calc(std::uint32_t from_index);

  std::uint32_t find_first_satisfy_conditions(std::uint32_t from_index,
                                              const std::function<bool(std::uint32_t)>& condition);

  void get_possible_movements(std::vector<std::uint32_t>& movements,
                              std::vector<std::uint32_t>& costs, std::int32_t range);

  std::int32_t distance_to(std::uint32_t index);
  void path_to(std::uint32_t index, std::vector<std::uint32_t>& path);

 private:
  graph board_graph;
  std::vector<std::int32_t> distance_map_;
  std::vector<std::size_t> sequence_map_;
  std::uint32_t start_index_;
};

namespace board_helper {
void calc_straight(std::uint32_t from_index, std::vector<std::uint32_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void calc_diagonal(std::uint32_t from_index, std::vector<std::uint32_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void calc_directed(std::uint32_t from_index, std::vector<std::uint32_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range,
                   bool skip_obstacles = false);

void neighboring_fields(std::uint32_t for_index, std::vector<std::uint32_t>& fields,
                        bool available);

void circle(std::uint32_t for_index, std::vector<std::uint32_t>& fields, bool available);

void all_free(std::vector<std::uint32_t>& fields);

void all(std::vector<std::uint32_t>& fields);

}  // namespace board_helper
