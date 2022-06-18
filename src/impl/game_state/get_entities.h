#pragma once

#include <unordered_map>

std::unordered_map<std::uint32_t, std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>> get_entities();
