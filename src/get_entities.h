#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <turn_based/defs.h>

using entities_map =
    std::unordered_map<entity_id_t, std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>;

entities_map get_entities();
