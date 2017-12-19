//
// Created by abrde on 20.12.2017.
//

#ifndef PIGEONWAR_MAGIC_POWER_MANAGER_H
#define PIGEONWAR_MAGIC_POWER_MANAGER_H

#include "managers.h"

struct power_field {
    power_field() = default;
    explicit power_field(int power) : power(power), base_power(base_power) {}
    int power;
    int base_power;
};

class powers_manager : public base_manager<power_field, power_field>
{
public:
    static inline void add_component(std::size_t entity_id, const managed_component_type& component)
    {
        managed_component_type power_component = component;
        power_component.power = power_component.base_power;
        base_manager<power_field, power_field>::add_component(entity_id, power_component);
    }
    static inline void modify_power_by(std::size_t entity_id, int value) {
        component_reference_for(entity_id).power += value;
    }
    static inline void set_power_to(std::size_t entity_id, int value) {
        component_reference_for(entity_id).power = value;
    }
    static inline void set_power_to_base_power(std::size_t entity_id) {
        auto& power_pack = component_reference_for(entity_id);
        power_pack.power = power_pack.base_power;
    }
    static inline int get_power_for(std::size_t entity_id) {
        return component_for(entity_id).power;
    }
    static inline int get_base_power_for(std::size_t entity_id) {
        return component_for(entity_id).base_power;
    }
};

template <>
inline void add_component_of_type<power_field>(std::size_t entity_id, const power_field& component) {
    powers_manager::add_component(entity_id, component);
}

#endif //PIGEONWAR_MAGIC_POWER_MANAGER_H
