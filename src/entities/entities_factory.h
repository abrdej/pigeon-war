#pragma once

#include "entity.h"

struct entities_factory {
    static std::uint32_t create(const std::string& entity_name);
};
