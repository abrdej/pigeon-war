//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_ADDITIONS_MANAGER_H
#define PIGEONWAR_ADDITIONS_MANAGER_H

#include "managers.h"
#include <memory>
#include <typeindex>

struct addition {
    std::unordered_map<std::type_index, std::shared_ptr<void>> data;

    template <typename T>
    T& get() {
        return data.at(std::type_index(typeid(T)));
    }
    template <typename T>
    const T& get() const {
        return data.at(std::type_index(typeid(T)));
    }
    template <typename T, typename... Args>
    void put(const std::shared_ptr<T>& x) {
        data[std::type_index(typeid(T))] = x;
    };
    template <typename T>
    void destroy() {
        data.erase(std::type_index(typeid(T)));
    }
};

struct additions_manager : base_manager<addition, addition&> {

    template <typename T, typename... Args>
    static inline void add_component(std::size_t entity_id, Args&&... args) {
        auto elem = std::make_shared<T>(args...);
        map_[entity_id].put<T>(elem);
        elem->destroyer = [entity_id]() {
            map_[entity_id].destroy<T>();
        };
    }

    template <typename T>
    static inline void get_component(std::size_t entity_id) {
        map_[entity_id].get<T>();
    }
};


#endif //PIGEONWAR_ADDITIONS_MANAGER_H
