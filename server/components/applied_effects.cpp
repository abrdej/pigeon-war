#include "applied_effects.h"

void remove_negative_effects(std::uint32_t entity_id) {
    auto& entity_effects = entity_manager::get(entity_id).get<applied_effects>()->named_data;
    std::vector<std::string> effects_to_remove;
    for (auto&& effect_pack : entity_effects) {
        if (effect_pack.second->is_effect_removable()
            && effect_pack.second->get_effect_type() == effect_types::negative) {
            effects_to_remove.emplace_back(effect_pack.first);
        }
    }
    for (auto&& effect_name : effects_to_remove) {
        entity_effects.erase(effect_name);
    }
}