#include <arrow.h>

#include <turn_based/damage_dealers.h>
#include <components/applied_effects.h>
#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

arrow::arrow(std::uint32_t entity_id)
  : path_target_ability(3), entity_id(entity_id) {}

void arrow::prepare(std::uint32_t for_index) {

    path_target_ability::prepare(for_index);

    game_control().custom_valid_targets[game_board().at(for_index)].clear();
    std::unordered_set<std::uint32_t> valid_targets;

    for (auto&& index : game_control().possible_movements_) {
        if (game_control().valid_target(index)) {
            valid_targets.insert(index);
        }
    }

    game_control().custom_valid_targets[game_board().at(for_index)] = std::move(valid_targets);

    for (auto&& entity_with_viewfinder : entities_with_viewfinder) {
        if (game::get<entity_manager>().alive(entity_with_viewfinder)) {
            game_control().custom_valid_targets[game_board().at(for_index)].insert(game_board().index_for(entity_with_viewfinder));
            game_control().possible_movements_.push_back(game_board().index_for(entity_with_viewfinder));
        }
    }

    game_control().custom_valid_target_type = game_control().custom_target_type::board_index;
}

void arrow::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    sender::send(make_action_message("arrow", game_control().selected_index_, index_on));

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(index_on), entity_id));

    auto caster_id = entity_id;

    if (game::get<entity_manager>().alive(enemy_id)) {
        auto viewfinder_connection =
                make_after_n_round_callback_holder(viewfinder_duration,
                                                   [this, enemy_id, caster_id](const turn_callback_info& info) mutable {
                                                       if (info.is_ending) {
                                                           if (game::get<entity_manager>().alive(enemy_id)) {
                                                               remove_effect(enemy_id, "viewfinder");
                                                           }
                                                           if (game::get<entity_manager>().alive(caster_id)) {
                                                               this->entities_with_viewfinder.erase(enemy_id);
                                                           }
                                                       }
                                                   });

        auto viewfinder_effect = make_negative_effect("viewfinder");
        viewfinder_effect->set_turn_connection(std::move(viewfinder_connection));
        viewfinder_effect->set_on_destruction([this, caster_id, enemy_id]() {
            if (game::get<entity_manager>().alive(caster_id)) {
                this->entities_with_viewfinder.erase(enemy_id);
            }
        });

        add_effect(enemy_id, viewfinder_effect);
        entities_with_viewfinder.insert(enemy_id);
    }

    used = true;
}
