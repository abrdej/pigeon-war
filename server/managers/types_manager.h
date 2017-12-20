#ifndef TYPES_MANAGER_H
#define TYPES_MANAGER_H

#include "common/managers.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <typeindex>

class types_manager : public base_manager<std::type_index, std::type_index>
{
};

#endif