//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_ADDITIONS_MANAGER_H
#define PIGEONWAR_ADDITIONS_MANAGER_H

#include "managers/entity_manager.h"
#include <memory>
#include <typeindex>

struct addition {
    std::unordered_map<std::string, std::shared_ptr<void>> named_data;

    template <typename T>
    std::shared_ptr<T> get_named(const std::string& name) {
        return std::static_pointer_cast<T>(named_data.at(name));
    }
    template <typename T>
    const std::shared_ptr<T> get_named(const std::string& name) const {
        return std::static_pointer_cast<T>(named_data.at(name));
    }
    template <typename T, typename... Args>
    void put_named(const std::string& name, const std::shared_ptr<T>& x) {
        named_data[name] = x;
    };
    void destroy_named(const std::string& name) {
        named_data.erase(name);
    }
	bool has(const std::string& name) const {
		return named_data.find(name) != std::end(named_data);
	}
};

template <typename T>
inline void add_component(std::uint32_t entity_id,
                          const std::string& name,
                          std::shared_ptr<T> x) {

    entity_manager::get(entity_id).get<addition>()->put_named(name, x);
}

inline void remove_component(std::uint32_t entity_id, const std::string& name) {
    entity_manager::get(entity_id).get<addition>()->destroy_named(name);
}

inline bool has_component(std::uint32_t entity_id, const std::string& name) {
    return entity_manager::get(entity_id).get<addition>()->has(name);
}

inline std::unordered_map<std::uint32_t, std::vector<std::string>> get_additions() {

    std::unordered_map<std::uint32_t, std::vector<std::string>> result;

    entity_manager::for_all([&result](base_entity entity) {

        if (entity.contain<addition>()) {
            std::shared_ptr<addition> additions_ptr = entity.get<addition>();

            auto& field = result[entity.entity_id];

            for (auto&& addition : additions_ptr->named_data) {
                field.push_back(addition.first);
            }
        }
    });
    return std::move(result);
}

#endif //PIGEONWAR_ADDITIONS_MANAGER_H
