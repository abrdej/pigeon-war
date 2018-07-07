//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_ADDITIONS_MANAGER_H
#define PIGEONWAR_ADDITIONS_MANAGER_H

#include "managers/entity_manager.h"
#include <memory>
#include <typeindex>
#include <core/turn_system.h>
#include <effects/base_effect.h>

struct applied_effects {
    std::unordered_map<std::string, std::shared_ptr<applied_effect>> named_data;

    void put_named(const std::string& effect_name, std::shared_ptr<applied_effect> x) {
        named_data[effect_name] = std::move(x);
    };
    void destroy_named(const std::string& effect_name) {
        named_data.erase(effect_name);
    }
	bool has(const std::string& effect_name) const {
		return named_data.find(effect_name) != std::end(named_data);
	}
};

inline void add_effect(std::uint32_t entity_id, std::shared_ptr<applied_effect> x) {
    auto applied_effects_ptr = game::get<entity_manager>().get(entity_id).get<applied_effects>();
    if (applied_effects_ptr) {
        applied_effects_ptr->put_named(x->get_name(), x);
    }
}

inline void remove_effect(std::uint32_t entity_id, const std::string &effect_name) {
    game::get<entity_manager>().get(entity_id).get<applied_effects>()->destroy_named(effect_name);
}

inline bool has_effect(std::uint32_t entity_id, const std::string &effect_name) {
    return game::get<entity_manager>().get(entity_id).get<applied_effects>()->has(effect_name);
}

void remove_negative_effects(std::uint32_t entity_id);

inline std::unordered_map<std::uint32_t, std::vector<std::string>> get_effects() {

    std::unordered_map<std::uint32_t, std::vector<std::string>> result;

    game::get<entity_manager>().for_all([&result](base_entity entity) {

        if (entity.contain<applied_effects>()) {
            std::shared_ptr<applied_effects> effect_ptr = entity.get<applied_effects>();

            auto& field = result[entity.entity_id];

            for (auto&& effect : effect_ptr->named_data) {
                field.push_back(effect.second->get_name());
            }
        }
    });
    return std::move(result);
}

#endif //PIGEONWAR_ADDITIONS_MANAGER_H
