#include <core/states.h>
#include <core/board.h>
#include <entities/cannon.h>
#include <managers/entity_manager.h>
#include "build_cannon.h"

build_cannon::build_cannon() {
    onEveryRound([this]() {
        built = false;
    });
}

void build_cannon::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    auto pos = board::to_pos(for_index);
    auto pos_to_build = pos;
    pos_to_build.second += 1;

    states::state_controller::possible_movements_.clear();
    states::state_controller::possible_movements_.push_back(board::to_index(pos_to_build.first, pos_to_build.second));

    states::state_controller::actual_targeting_type_ = states::target_types::moving;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void build_cannon::use(size_t index_on) {

    if (built)
        return;

    auto cannon_id = entity_manager::create<cannon>();
    auto player = players::active_player_name();
    players::add_entity_for_player(player, cannon_id);

    board::insert(index_on, cannon_id);
}