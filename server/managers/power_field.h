//
// Created by abrde on 20.12.2017.
//

#ifndef PIGEONWAR_MAGIC_POWER_MANAGER_H
#define PIGEONWAR_MAGIC_POWER_MANAGER_H

#include <cstdint>


struct power_field {
    power_field() = default;
    explicit power_field(std::int32_t power) : power(power), base_power(base_power) {}
    std::int32_t power;
	std::int32_t base_power;
};

#endif //PIGEONWAR_MAGIC_POWER_MANAGER_H
