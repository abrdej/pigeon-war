#pragma once

#include <turn_based/defs.h>
#include <turn_based/module_holder.h>

/**
 * @brief Class representing the entity.
 * It can store different modules that built up the entity.
 */
struct base_entity : module_holder {
  entity_id_t entity_id{null_entity_id};
  std::string name;
};
