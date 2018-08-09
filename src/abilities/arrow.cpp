#include "arrow.h"
#include <core/board.h>
#include <server/sender.h>
#include <components/applied_effects.h>
#include <utils/logging.h>
#include <messages/make_message.h>
#include "managers/entity_manager.h"
#include "damage_dealers.h"

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
        LOG_DEBUG() << "arrow was used\n";
        return;
    }

    auto from_index = game_control().selected_index_;
    auto caster_id = game_board().at(from_index);

    sender::send(make_action_message("arrow", from_index, index_on));

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(index_on), caster_id));

    if (game::get<entity_manager>().alive(enemy_id)) {

        auto viewfinder_connection =
                make_after_n_round_callback_holder(viewfinder_duration,
                                                   [this, enemy_id, caster_id](const turn_callback_info& info) mutable {

                                                       if (info.ended) {

                                                           if (game::get<entity_manager>().alive(enemy_id)) {
                                                               remove_effect(enemy_id,
                                                                             "viewfinder");
                                                               LOG_DEBUG() << "remove viewfinder from entity of id:" << enemy_id << "\n";
                                                           }

                                                           if (game::get<entity_manager>().alive(caster_id)) {
                                                               this->entities_with_viewfinder.erase(enemy_id);
                                                               LOG_DEBUG() << "erase entity of id:" << enemy_id << " from entities with viewfinder\n";
                                                           }
                                                       }
                                                   });

        auto viewfinder_effect = make_negative_effect("viewfinder");
        viewfinder_effect->set_turn_connection(std::move(viewfinder_connection));
        viewfinder_effect->set_on_destruction([this, caster_id, enemy_id]() {
            if (game::get<entity_manager>().alive(caster_id)) {
                this->entities_with_viewfinder.erase(enemy_id);
                LOG_DEBUG() << "erase entity of id:" << enemy_id << "from entities with viewfinder\n";
            }
        });

        add_effect(enemy_id, viewfinder_effect);
        LOG_DEBUG() << "add effect of viewfinder to entity of id:" << enemy_id << "\n";

        entities_with_viewfinder.insert(enemy_id);
        LOG_DEBUG() << "insert entity of id:" << enemy_id << " into entities with viewfinder\n";
    }

    used = true;
}