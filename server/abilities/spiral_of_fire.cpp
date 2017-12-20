#include <core/states_controller.h>
#include <core/board.h>
#include <entities/creature.h>
#include <gui/bitmap_center.h>
#include <common/managers.h>
#include <gui/entity_drawer.h>
#include <gui/drawing_manager.h>
#include "spiral_of_fire.h"
#include "damage_dealers.h"
#include "managers/abilities_manager.h"

spiral_of_fire::spiral_of_fire() {

}

void spiral_of_fire::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                range, true);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void spiral_of_fire::use(size_t index_on) {

    if (!can_be_used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    auto from_pos = board::to_pos(index_on);
    auto to_pos = board::to_pos(used_from_index);

    int xx = static_cast<int>(from_pos.first) - static_cast<int>(to_pos.first);
    int yy = static_cast<int>(from_pos.second) - static_cast<int>(to_pos.second);

    auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

    play_animation(used_from_index, index_to_move);

    std::vector<std::size_t> indexes;

    if (xx != 0) {
        for (int x = xx > 0 ? 1 : -1; std::abs(x) <= std::abs(xx); x = xx > 0 ? x + 1 : x - 1) {

            auto index = board::to_index(to_pos.first + x, to_pos.second);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(x) != std::abs(xx)) {
                    indexes.push_back(index);
                }
            }
        }
    } else {
        for (int y = yy > 0 ? 1 : -1; abs(y) <= abs(yy); y = yy > 0 ? y + 1 : y - 1) {

            auto index = board::to_index(to_pos.first, to_pos.second + y);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(y) != std::abs(yy)) {
                    indexes.push_back(index);
                }
            }
        }
    }

    for (int i = indexes.size() - 1; i >= 0; --i) {
        if (!board::empty(indexes[i])) {
            damage_dealers::standard_damage_dealer(special_damage(damage, board::at(indexes[i]), entity_id));
        }
    }
    can_be_used = false;

    auto ability = abilities_manager::component_for(entity_id).type(abilities::ability_types::offensive);
    std::shared_ptr<chopper> ch = std::static_pointer_cast<chopper>(ability);
    ch->remove_fired();
}

void spiral_of_fire::play_animation(size_t from_index, size_t to_index) {

    auto entity_id = board::take(from_index);

    bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::spiral_of_fire;

    animations_queue::push_animation(animation_types::move,
                                     from_index,
                                     to_index,
                                     entity_id,
                                     bitmap_key::none);

    animations_queue::push_animation(animation_types::move,
                                     to_index,
                                     from_index,
                                     entity_id,
                                     bitmap_key::none);

    bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::creature;

    board::give_back(entity_id, from_index);
}