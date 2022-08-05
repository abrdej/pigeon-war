#include <trash_trail.h>

#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <talons.h>
#include <components/damage_taker.h>
#include <turn_based/game.h>
#include <turn_based/managers/players_manager.h>

trash_trail::trash_trail(std::uint32_t entity_id) : entity_id_(entity_id) {
  on_every_two_turns_from_next([entity_id]() {
    auto entity_abilities = game_get<entity_manager>().get(entity_id).get<abilities>();
    auto moveable_ptr = std::dynamic_pointer_cast<moveable>(entity_abilities->of_type(ability_types::moving));
    if (moveable_ptr) {
      moveable_ptr->remove_slow_down();
      moveable_ptr->skip_collisions(false);
    }
  });

  connection_ = game_get<damage_manager>().on_receive_damage(
      [entity_id, activation_health_amount = activation_health_amount_](const damage_pack& dmg) {
        auto receiver_id = dmg.damage_receiver_id;
        auto& players_manager_ref = game_get<players_manager>();
        auto player_id = players_manager_ref.player_for_entity(entity_id);
        if (players_manager_ref.enemy_entity(player_id, receiver_id)) {
          auto enemy_health =
              game_get<entity_manager>().get(receiver_id).get<health_field>()->health;
          if (enemy_health <= activation_health_amount && enemy_health > 0) {
            auto entity_abilities = game_get<entity_manager>().get(entity_id).get<abilities>();
            auto talons_ptr = entity_abilities->get<talons>();
            talons_ptr->set_trash_trail_enemy_id(receiver_id);

            auto moveable_ptr = std::dynamic_pointer_cast<moveable>(entity_abilities->of_type(ability_types::moving));
            if (moveable_ptr) {
              moveable_ptr->set_slow_down(6);
              moveable_ptr->skip_collisions(true);
            }

            sender::send(make_action_message("trash_trail", game_board().index_for(receiver_id)));
          }
        }
      },
      on_receive_damage_policy::after);
}

trash_trail::~trash_trail() { connection_.disconnect(); }
