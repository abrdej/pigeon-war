#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <core/board.h>
#include <core/path_finder.h>
#include <effects/base_effect.h>
#include <managers/entity_manager.h>

class auras_observer {
    std::unordered_map<std::uint32_t, std::shared_ptr<effect>> auras;
    std::vector<std::pair<std::uint32_t, std::shared_ptr<effect>>> entities_with_auras;
public:
    auras_observer();
    void add_aura(std::uint32_t for_entity, const std::shared_ptr<effect>& aura);
    void remove_aura(std::uint32_t from_entity);
    void observe();
};
