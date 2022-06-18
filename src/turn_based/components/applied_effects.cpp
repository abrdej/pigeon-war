#include <turn_based/components/applied_effects.h>

void remove_negative_effects(std::uint32_t entity_id) {
  auto& entity_effects =
      game::get<entity_manager>().get(entity_id).get<applied_effects>()->named_data;
  std::vector<std::string> effects_to_remove;
  for (auto&& effect_pack : entity_effects) {
    if (effect_pack.second->is_effect_removable() &&
        effect_pack.second->get_effect_type() == effect_types::negative) {
      effects_to_remove.emplace_back(effect_pack.first);
    }
  }
  for (auto&& effect_name : effects_to_remove) {
    entity_effects.erase(effect_name);
  }
}

std::unordered_map<std::uint32_t, std::vector<std::string>> get_effects() {
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
