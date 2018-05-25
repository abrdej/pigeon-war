#include "eye_shoot.h"

#include <core/board.h>
#include <abilities/damage_dealers.h>

eye_shoot::eye_shoot() {

}

void eye_shoot::use(std::uint32_t to_index) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(from_index);

    sender::send(make_action_message("eye_shoot", from_index, to_index));

    damage_dealers::standard_damage_dealer(ranged_damage(base_damage,
                                                         board::at(to_index),
                                                         entity_id));

    auto from_pos = board::to_pos(from_index);
    auto to_pos = board::to_pos(to_index);

    auto dx = from_pos.first - to_pos.first;
    auto dy = from_pos.second - to_pos.second;

    std::uint32_t index_shoot;
    std::vector<std::uint32_t> sides_indexes;

    std::array<int, 2> shifts{1, 2};
    std::vector<std::uint32_t> indexes;
    if (dx == 0) {
        for (int i = -1; i <= 1; i+=2) {
            for (auto shift : shifts) {
                auto index = board::to_index(to_pos.first + i * shift, to_pos.second);
                index_shoot = index;
                if (!board::empty(index)) {
                    indexes.emplace_back(index);
                    break;
                }
            }
            sides_indexes.emplace_back(index_shoot);
        }
    } else {
        for (int i = -1; i <= 1; i+=2) {
            for (auto shift : shifts) {
                auto index = board::to_index(to_pos.first, to_pos.second + i * shift);
                index_shoot = index;
                if (!board::empty(index)) {
                    indexes.emplace_back(index);
                    break;
                }
            }
            sides_indexes.emplace_back(index_shoot);
        }
    }

    sender::send(make_action_message("eye_shoot_to_sides", to_index, sides_indexes));

    for (auto&& index : indexes) {
        if (!board::empty(index))
            damage_dealers::standard_damage_dealer(ranged_damage(side_damage,
                                                                 board::at(index),
                                                                 entity_id));
    }

    used = true;
}
