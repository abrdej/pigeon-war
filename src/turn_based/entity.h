#pragma once

#include <limits>

#include <turn_based/components/health_field.h>
#include <turn_based/defs.h>
#include <turn_based/module_holder.h>

enum class directions { right, left };

//static constexpr auto none_entity_id = std::numeric_limits<std::uint32_t>::max();

struct base_entity : module_holder {
  static constexpr entity_id_t no_id{null_entity_id};
  entity_id_t entity_id{no_id};
  std::string name;
};
