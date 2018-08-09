#pragma once

#include <string>

std::string read_map_from_json(const std::string& json_file, std::pair<uint32_t, uint32_t>& map_size);
