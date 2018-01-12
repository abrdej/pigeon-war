//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_ADDITIONS_MANAGER_H
#define PIGEONWAR_ADDITIONS_MANAGER_H

#include "common/managers.h"
#include <memory>
#include <typeindex>
#include <SFML/Config.hpp>

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

struct additions_manager : base_manager<addition, addition&> {

    template <typename T>
    static inline void add_component(sf::Uint64 entity_id,
                                     const std::string& name,
                                     std::shared_ptr<T> x) {

		auto it = map_.find(entity_id);
		if (it != std::end(map_)) {
			it->second.put_named(name, x);
		}
		else {
			it = map_.emplace(entity_id, addition()).first;
			it->second.put_named(name, x);
			entity_remover::add_remover(entity_id, [entity_id]() {
				map_.erase(entity_id);
			});
		}
    }

    static void remove_component(sf::Uint64 entity_id, const std::string& name) {
        map_[entity_id].destroy_named(name);
    }

	static bool has_component(sf::Uint64 entity_id, const std::string& name) {
		return map_[entity_id].has(name);
	}

	static std::unordered_map<sf::Uint64, std::vector<std::string>> get_map() {
		std::unordered_map<sf::Uint64, std::vector<std::string>> result;

		for (auto&& elem : map_) {

			auto& field = result[elem.first];

			for (auto&& addition : elem.second.named_data) {
				field.push_back(addition.first);
			}
		}

		return std::move(result);
	}
};


#endif //PIGEONWAR_ADDITIONS_MANAGER_H
