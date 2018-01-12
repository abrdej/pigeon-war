//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_ENTITY_REMOVER_H
#define PIGEONWAR_ENTITY_REMOVER_H


#include <functional>
#include <vector>
#include <unordered_map>
#include <SFML/Config.hpp>

class entity_remover {
    using remover_type = std::function<void()>;
    using removers_vector = std::vector<remover_type>;

    static std::unordered_map<sf::Uint64, removers_vector> removers;
public:
    static void add_remover(sf::Uint64 entity_id, const remover_type& x) {
        removers[entity_id].push_back(x);
    }
    static void remove(sf::Uint64 entity_id) {
        auto it = removers.find(entity_id);
        if (it != std::end(removers)) {
            for (auto&& remover : it->second) {
                remover();
            }
            removers.erase(it);
        }
    }
};


#endif //PIGEONWAR_ENTITY_REMOVER_H
