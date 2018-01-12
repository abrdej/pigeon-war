#include <core/states_controller.h>
#include <core/board.h>
#include <entities/shooter.h>
#include <managers/entity_manager.h>
#include <entities/barrack.h>
#include "build_barrack.h"

build_barrack::build_barrack() {
    onEveryRound([this]() {
        built = false;
    });
}

void build_barrack::prepare(sf::Uint64 for_index) {
    states::state_controller::selected_index_ = for_index;

    auto pos = board::to_pos(for_index);
    auto pos_to_build = pos;
    pos_to_build.second += 1;

    states::state_controller::possible_movements_.clear();
    states::state_controller::possible_movements_.push_back(board::to_index(pos_to_build.first, pos_to_build.second));

    states::state_controller::actual_targeting_type_ = states::target_types::moving;
    states::state_controller::wait_for_action([this](sf::Uint64 index)
                                              {
                                                  return use(index);
                                              });
}

void build_barrack::use(sf::Uint64 index_on) {

    if (built)
        return;

    auto barrack_id = entity_manager::create<barrack>();
    auto player_id = players_manager::get_active_player_id();
    players_manager::add_entity_for_player(player_id, barrack_id);

    board::insert(index_on, barrack_id);
}