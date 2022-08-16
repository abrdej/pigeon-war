#include <counterattack.h>

#include <logging/logger.h>
#include <turn_based/board_helpers.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/game_controller.h>

counterattack::counterattack(entity_id_t entity_id)
    : passive_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {
  on_receive_damage(entity_id, [this](const damage_pack& dmg) {

    if (game::get<entity_manager>().get(entity_id_).get<health_field>()->health > 0) {
      auto enemy_index = game_board().index_for(dmg.damage_dealer_id);

      std::vector<index_t> neighbors;
      board_helper::neighboring_fields(game_board().index_for(entity_id_), neighbors, false);

      for (auto index : neighbors) {
        if (index == enemy_index) {
          use(enemy_index);
          break;
        }
      }
    }
  }, on_receive_damage_policy::after);

  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Counterattack setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void counterattack::use(index_t index_on) {
  if (used) {
    return;
  }

  sender::send(make_action_message(name, entity_id_, index_on));

  damage_dealers::standard_damage_dealer(melee_damage(damage_, game_board().at(index_on), entity_id_));

  used = true;
}
