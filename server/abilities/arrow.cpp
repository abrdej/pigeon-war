#include "arrow.h"
#include <core/board.h>
#include <sender.h>
#include <common/animations.h>
#include <components/additions.h>
#include "managers/entity_manager.h"
#include "damage_dealers.h"

std::string arrow::hint() const {
    return "";
}

void arrow::prepare(std::uint32_t for_index) {

    path_target_ability::prepare(for_index);

    states::state_controller::custom_valid_targets[board::at(for_index)].clear();
    std::unordered_set<std::uint32_t> valid_targets;

    for (auto&& index : states::state_controller::possible_movements_) {
        if (states::state_controller::valid_target(index)) {
            valid_targets.insert(index);
        }
    }

    states::state_controller::custom_valid_targets[board::at(for_index)] = std::move(valid_targets);

    for (auto&& entity_with_viewfinder : entities_with_viewfinder) {
        if (entity_manager::alive(entity_with_viewfinder)) {
            states::state_controller::custom_valid_targets[board::at(for_index)].insert(board::index_for(entity_with_viewfinder));
            states::state_controller::possible_movements_.push_back(board::index_for(entity_with_viewfinder));
        }
    }

    states::state_controller::custom_valid_target_type = states::state_controller::custom_target_type::board_index;

}

void arrow::use(std::uint32_t index_on) {
    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(from_index);

    sender::send(message_types::animation, animation_def::arrow, from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), caster_id));

    if (entity_manager::alive(enemy_id)) {

        auto viewfinder_receiver = make_after_n_round_callback_holder(viewfinder_duration,
                                                                      [this, enemy_id, caster_id](const turn_callback_info& info) mutable {

//                                                                      sender::send(message_types::animation, animation_def::poison, board::index_for(enemy_id));

                                                                          if (info.ended) {

                                                                              if (entity_manager::alive(enemy_id)) {
                                                                                  remove_component(enemy_id,
                                                                                                   "viewfinder_effect");
                                                                              }

                                                                              if (entity_manager::alive(caster_id)) {
																				  this->entities_with_viewfinder.erase(enemy_id);
                                                                              }
                                                                          }
                                                                      });

        add_component(enemy_id,
                      "viewfinder_effect",
                      std::move(viewfinder_receiver));

        entities_with_viewfinder.insert(enemy_id);
    }

    used = true;
}