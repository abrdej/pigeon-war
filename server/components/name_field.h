#ifndef NAMES_MANAGER_H
#define NAMES_MANAGER_H

#include <vector>
#include <string>

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

#endif