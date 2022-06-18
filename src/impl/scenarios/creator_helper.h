#pragma once

#include <cstdlib>
#include <string>
#include <vector>

namespace creator_helper {

using pos_type = std::pair<std::uint32_t, std::uint32_t>;

pos_type pos(std::uint32_t col, std::uint32_t row);

void create_neutral_many(const std::string& entity_name, const std::vector<pos_type>& positions);

void create_around_map(const std::string& name);

}  // namespace creator_helper
