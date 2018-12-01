#include <managers/get_entity_names.h>

#include <core/game.h>
#include <managers/entity_manager.h>

std::unordered_map<std::uint32_t, std::string> get_entity_names() {
    std::unordered_map<std::uint32_t, std::string> entity_names;
    game::get<entity_manager>().for_all([&entity_names](const base_entity& entity) {
        entity_names.emplace(entity.entity_id, entity.name);
    });
    return entity_names;
}
