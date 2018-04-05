#include "eye_shoot.h"

#include <core/board.h>
#include <abilities/damage_dealers.h>

void eye_shoot::use(std::uint32_t to_index) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(from_index);

    sender::send(make_action_message("eye_shoot", from_index, to_index));

    auto final_damage = damage_dealers::standard_damage_dealer(ranged_damage(base_damage,
                                                                             board::at(to_index),
                                                                             entity_id));




    used = true;
}
