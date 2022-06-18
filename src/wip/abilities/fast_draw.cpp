#include <fast_draw.h>

#include <turn_based/damage_dealers.h>
#include <components/damage_taker.h>
#include <turn_based/game_controller.h>
#include <turn_based/utils/algorithm.h>

fast_draw::fast_draw(std::uint32_t entity_id)
  : entity_id(entity_id) {

  on_receive_damage(entity_id, [this](const damage_pack& dmg) {

    if (game::get<entity_manager>().get(this->entity_id).get<health_field>()->health > 0) {
      auto enemy_index = game_board().index_for(dmg.damage_dealer_id);

      if (dmg.damage_type == damage_types::RANGED) {
        path_finder path_finder(true);
        path_finder.calc(game_board().index_for(this->entity_id));

        std::vector<std::uint32_t> possible_movements;
        std::vector<std::uint32_t> possible_movements_costs;

        path_finder.get_possible_movements(possible_movements,
                                           possible_movements_costs,
                                           range);
        if (has_value(possible_movements, enemy_index)) {
          use(enemy_index);
        }
      }
    }
  }, on_receive_damage_policy::after);
}

void fast_draw::use(std::uint32_t index_on) {
  sender::send(make_action_message("fast_draw", game_board().index_for(this->entity_id), index_on));
  damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(index_on), entity_id));
}
