#pragma once

#include <limits>
#include "core/module_holder.h"
#include "components/health_field.h"

enum class directions {
    right, left
};

struct base_entity : module_holder {
    static constexpr uint32_t no_id{std::numeric_limits<uint32_t>::max()};
    uint32_t entity_id{no_id};

    std::string name;
};

#define DEFINE_ENTITY(name) \
struct name final { \
    static void create(base_entity& entity); \
};
