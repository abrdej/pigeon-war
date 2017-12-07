#include "drawer_factory.h"

std::unordered_map<std::type_index, drawer_factory::drawer_creator> drawer_factory::drawer_creators;

bool drawer_factory::initialized = false;
