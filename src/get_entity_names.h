#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <turn_based/defs.h>

std::unordered_map<entity_id_t, std::string> get_entity_names();

std::unordered_map<entity_id_t, std::uint32_t> get_entity_players();
