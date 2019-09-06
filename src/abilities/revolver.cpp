#include <abilities/revolver.h>

#include <abilities/damage_dealers.h>
#include <components/damage_taker.h>
#include <core/game_controller.h>

revolver::revolver(std::uint32_t entity_id)
  : path_target_ability(3),
    entity_id(entity_id) {
  on_every_two_turns_from_next([this]() {
    used = false;
    additional_shot = false;
  });
}

void revolver::use(std::uint32_t index_on) {
  if (used) {
    return;
  }

  const auto enemy_id = game_board().at(index_on);

  sender::send(make_action_message("revolver", game_board().index_for(this->entity_id), index_on));
  damage_dealers::standard_damage_dealer(ranged_damage(
    additional_shot ? damage : damage + additional_damage, enemy_id, entity_id));

  if (!game_get<entity_manager>().alive(enemy_id)) {
    additional_shot = true;
    return;
  }

  if (additional_shot) {
    additional_shot = false;
    used = true;
    return;
  }

  sender::send(make_action_message("revolver", game_board().index_for(this->entity_id), index_on));
  damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(index_on), entity_id));

  used = true;
}
