#include <core/states_controller.h>
#include <core/board.h>
#include <managers/players_manager.h>
#include <components/applied_effects.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include "kill.h"
#include "damage_dealers.h"
#include "sender.h"

kill::kill() {

}

void kill::prepare(std::uint32_t for_index) {
    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);

    std::vector<std::uint32_t> possible_fields;
    std::vector<std::uint32_t> costs;
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       costs,
                                       range);

    states::state_controller::actual_targeting_type_ = target_types::enemy;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return set_landing(index);
                                              });
}

void kill::set_landing(std::uint32_t for_index) {

    target_index = for_index;

    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, true);

    if (states::state_controller::possible_movements_.empty()) {
        return;
    }

    states::state_controller::actual_targeting_type_ = target_types::moving;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });

}

void kill::use(std::uint32_t index_on) {

    states::state_controller::possible_movements_.clear();

    auto used_from_index = states::state_controller::selected_index_;

    auto entity_id = game::get<board>().at(used_from_index);

    bool is_killer_instinct_active = has_effect(entity_id, "killer_instinct");

    sender::send(make_action_message("kill", used_from_index, index_on, target_index));

    game::get<board>().move(used_from_index, index_on);

    states::state_controller::selected_index_ = index_on;

    auto enemy_id = game::get<board>().at(target_index);

    damage_dealers::standard_damage_dealer(melee_damage(is_killer_instinct_active ? damage_with_killer_instinct : damage, enemy_id, entity_id));
}