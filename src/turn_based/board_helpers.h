#pragma once

#include <vector>

#include <turn_based/defs.h>

namespace board_helper {

void calc_straight(index_t from_index,
                   std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs,
                   std::int32_t range,
                   bool skip_obstacles = false);

void calc_diagonal(index_t from_index,
                   std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs,
                   std::int32_t range,
                   bool skip_obstacles = false);

void calc_directed(index_t from_index,
                   std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs,
                   std::int32_t range,
                   bool skip_obstacles = false);

void neighboring_fields(index_t for_index, std::vector<index_t>& fields, bool available);

void circle(index_t for_index, std::vector<index_t>& fields, bool available);

void all_free(std::vector<index_t>& fields);

void all(std::vector<index_t>& fields);

}  // namespace board_helper
