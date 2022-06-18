#pragma once

#include <unordered_map>

using entities_map =
    std::unordered_map<std::uint32_t, std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>;

entities_map get_entities();
