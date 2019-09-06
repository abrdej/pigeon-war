#include <effects/aura_of_destruction_effect.h>

#include <components/modification.h>
#include <components/power_field.h>
#include <managers/entity_manager.h>

bool aura_of_destruction_effect::set_effect(std::uint32_t entity_id) {
  auto aura_power = game::get<entity_manager>().get(this->entity_id).get<power_filed>()->power;

  auto player_id = game::get<players_manager>().player_for_entity(this->entity_id);

  if (aura_power > 0 && player_id != players_ids::no_player_id &&
      game::get<players_manager>().player_entity(player_id, entity_id) &&
      game::get<entity_manager>().get(entity_id).contain<modification>()) {
    std::cout << "Apply aura\n";

    game::get<entity_manager>().get(entity_id).get<modification>()->modify_by(
        modifiers::damage_dealer, damage_increase);

    return true;
  }
  return false;
}

void aura_of_destruction_effect::remove_effect(std::uint32_t entity_id) {
  game::get<entity_manager>().get(entity_id).get<modification>()->modify_by(
      modifiers::damage_dealer, -damage_increase);
}
