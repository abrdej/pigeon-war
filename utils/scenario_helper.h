//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SCENARIO_HELPER_H
#define PIGEONWAR_SCENARIO_HELPER_H

#include <initializer_list>
#include <memory>
#include "managers/entity_remover.h"

template <typename Callback>
void if_any_die(std::initializer_list<std::size_t> entities_id, Callback callback) {
    auto any_die = [callback](){
        callback();
    };
    for (auto&& entity_id : entities_id) {
        entity_remover::add_remover(entity_id, any_die);
    }
}

template <typename Callback>
void if_any_die(std::vector<std::size_t> entities_id, Callback callback) {
    auto any_die = [callback](){
        callback();
    };
    for (auto&& entity_id : entities_id) {
        entity_remover::add_remover(entity_id, any_die);
    }
}

template <typename Callback>
void if_all_die(std::initializer_list<std::size_t> entities_id, Callback callback) {
    auto entities_size = entities_id.size();
    auto i = std::make_shared<int>(0);
    auto someone_die = [callback, entities_size, counter = i]() mutable {
        if (++(*counter) == entities_size) {
            callback();
        }
    };
    for (auto&& entity_id : entities_id) {
        entity_remover::add_remover(entity_id, someone_die);
    }
}

template <typename Callback>
void if_all_die(std::vector<std::size_t> entities_id, Callback callback) {
    auto entities_size = entities_id.size();
    auto i = std::make_shared<int>(0);
    auto someone_die = [callback, entities_size, counter = i]() mutable {
        if (++(*counter) == entities_size) {
            callback();
        }
    };
    for (auto&& entity_id : entities_id) {
        entity_remover::add_remover(entity_id, someone_die);
    }
}

#endif //PIGEONWAR_SCENARIO_HELPER_H
