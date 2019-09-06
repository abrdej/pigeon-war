#pragma once

#include <limits>

#include <components/health_field.h>
#include <core/defs.h>
#include <core/module_holder.h>

enum class directions { right, left };

static constexpr auto none_entity_id = std::numeric_limits<std::uint32_t>::max();

struct base_entity : module_holder {
  static constexpr id_t no_id{none_entity_id};
  id_t entity_id{no_id};
  std::string name;
};

#define DEFINE_ENTITY(name)                  \
  struct name final {                        \
    static void create(base_entity& entity); \
  };
