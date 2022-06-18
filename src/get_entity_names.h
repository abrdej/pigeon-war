#pragma once

#include <unordered_map>

std::unordered_map<std::uint32_t, std::string> get_entity_names();

std::unordered_map<std::uint32_t, std::uint32_t> get_entity_players();
