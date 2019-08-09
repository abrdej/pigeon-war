#include <abilities/transmission.h>

#include <server/sender.h>
#include <core/board.h>

transmission::transmission(std::uint32_t entity_id)
  : path_target_ability(4, target_types::all),
    entity_id(entity_id) {
}

void transmission::use(std::uint32_t on_index) {
  from_index = on_index;
  game_control().actual_targeting_type_ = target_types::moving;
  game_control().wait_for_action([this](std::uint32_t index) {
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
