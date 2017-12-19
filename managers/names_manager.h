#ifndef NAMES_MANAGER_H
#define NAMES_MANAGER_H

#include "managers.h"
#include <unordered_map>
#include <vector>
#include <string>

using names_manager = base_manager<std::string, std::string&>;

struct name_field {
    std::string value;

    name_field() = default;
    explicit name_field(std::string x) : value(std::move(x)) {}
    operator std::string() {
        return value;
    }
    operator std::string() const {
        return value;
    }
    name_field& operator=(std::string x) {
        this->value = std::move(x);
        return *this;
    }
};

template <>
inline void add_component_of_type<name_field>(std::size_t entity_id, const name_field& component) {
    std::string name = component;
    names_manager::add_component(entity_id, name);
}

#endif