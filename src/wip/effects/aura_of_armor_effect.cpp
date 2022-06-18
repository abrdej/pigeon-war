#include <aura_of_armor_effect.h>

#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>

bool aura_of_armor_effect::set_effect(std::uint32_t entity_id) {
  auto player_id = game::get<players_manager>().player_for_entity(this->entity_id);

  if (player_id != players_ids::no_player_id &&
      game::get<players_manager>().player_entity(player_id, entity_id) &&
      game::get<entity_manager>().get(entity_id).contain<modification>()) {
    LOG(debug) << "Apply aura";

    game::get<entity_manager>().get(entity_id).get<modification>()->modify_by(
        modifiers::damage_receiver, -damage_reduction);

    return true;
  }
  return false;
}

void aura_of_armor_effect::remove_effect(std::uint32_t entity_id) {
  if (game::get<entity_manager>().get(entity_id).contain<modification>()) {
    LOG(debug) << "Remove aura";

    game::get<entity_manager>().get(entity_id).get<modification>()->modify_by(
        modifiers::damage_receiver, damage_reduction);
  }
}
