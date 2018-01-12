#ifndef ABILITIES_MANAGER_H
#define ABILITIES_MANAGER_H

#include "common/managers.h"
#include "server/abilities/abilities.h"

struct abilities_manager : base_manager<abilities, abilities&>
{
};

template <>
inline void add_component_of_type<abilities>(sf::Uint64 entity_id, const abilities& component) {
    abilities_manager::add_component(entity_id, component);
}

#endif