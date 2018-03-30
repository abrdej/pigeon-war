#include <core/states_controller.h>
#include <core/board.h>
#include <entities/creature.h>
#include <managers/managers.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include "spiral_of_fire.h"
#include "damage_dealers.h"
#include "sender.h"

spiral_of_fire::spiral_of_fire() {

}

void spiral_of_fire::use(std::uint32_t index_on) {

    if (!can_be_used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    auto from_pos = board::to_pos(index_on);
    auto to_pos = board::to_pos(used_from_index);

    std::int32_t xx = static_cast<std::int32_t>(from_pos.first) - static_cast<std::int32_t>(to_pos.first);
    std::int32_t yy = static_cast<std::int32_t>(from_pos.second) - static_cast<std::int32_t>(to_pos.second);

    auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

    sender::send(make_action_message("spiral_of_fire", used_from_index, index_to_move));

    std::vector<std::uint32_t> indexes;

    if (xx != 0) {
        for (std::int32_t x = xx > 0 ? 1 : -1; std::abs(x) <= std::abs(xx); x = xx > 0 ? x + 1 : x - 1) {

            auto index = board::to_index(to_pos.first + x, to_pos.second);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(x) != std::abs(xx)) {
                    indexes.push_back(index);
                }
            }
        }
    } else {
        for (std::int32_t y = yy > 0 ? 1 : -1; abs(y) <= abs(yy); y = yy > 0 ? y + 1 : y - 1) {

            auto index = board::to_index(to_pos.first, to_pos.second + y);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(y) != std::abs(yy)) {
                    indexes.push_back(index);
                }
            }
        }
    }

    for (std::int32_t i = indexes.size() - 1; i >= 0; --i) {
        if (!board::empty(indexes[i])) {
            damage_dealers::standard_damage_dealer(special_damage(damage, board::at(indexes[i]), entity_id));
        }
    }
    can_be_used = false;

    auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
    std::shared_ptr<chopper> chopper_ptr = abilities_ptr->get<chopper>();
    chopper_ptr->remove_fired();
}