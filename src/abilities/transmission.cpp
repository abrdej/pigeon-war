#include "transmission.h"

#include <server/sender.h>
#include <core/board.h>

transmission::transmission(std::uint32_t entity_id)
        : entity_id(entity_id) {

}

void transmission::use(std::uint32_t from_index) {

    this->from_index = from_index;

    //path_finder path_finder;
    //path_finder.calc(game_board().index_for(entity_id));
    //path_finder.get_possible_movements(game_control().possible_movements_,
    //                                   game_control().possible_movements_costs_,
    //                                   range);

    game_control().actual_targeting_type_ = target_types::moving;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return transmit(index);
                                              });
}

void transmission::transmit(std::uint32_t to_index) {

    if (used)
        return;

    sender::send(make_action_message("transmission", from_index, to_index));

    game_board().move(from_index, to_index);

    game_control().possible_movements_.clear();

    used = true;
}