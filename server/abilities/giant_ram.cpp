#include "giant_ram.h"
#include <core/states_controller.h>
#include <core/board.h>
#include <gui/bitmap_center.h>
#include <common/managers.h>
#include "managers/bitmap_field_manager.h"
#include "damage_dealers.h"
#include "managers/abilities_manager.h"

giant_ram::giant_ram(sf::Uint64 entity_id) : entity_id(entity_id) {

}

void giant_ram::prepare(sf::Uint64 for_index) {

    straight_target_ability::prepare(for_index);

    for (auto& index : states::state_controller::possible_movements_) {
        if (board::empty(index)) {
            states::state_controller::custom_valid_targets[entity_id].insert(index);
        }
    }

    states::state_controller::custom_valid_target_type = states::state_controller::custom_target_type::board_index;
}

void giant_ram::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    auto from_pos = board::to_pos(index_on);
    auto to_pos = board::to_pos(used_from_index);

    sf::Int32 xx = static_cast<sf::Int32>(from_pos.first) - static_cast<sf::Int32>(to_pos.first);
    sf::Int32 yy = static_cast<sf::Int32>(from_pos.second) - static_cast<sf::Int32>(to_pos.second);

    auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

    sender::send(message_types::animation, animation_def::giant_ram, used_from_index, index_to_move);

    board::move(used_from_index, index_to_move);

    std::vector<sf::Uint64> indexes;

    if (xx != 0) {
        for (sf::Int32 x = xx > 0 ? 1 : -1; std::abs(x) < std::abs(xx); x = xx > 0 ? x + 1 : x - 1) {

            auto index = board::to_index(to_pos.first + x, to_pos.second);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(x) != std::abs(xx)) {
                    indexes.push_back(index);
                }
            }
        }
    } else {
        for (sf::Int32 y = yy > 0 ? 1 : -1; abs(y) < abs(yy); y = yy > 0 ? y + 1 : y - 1) {

            auto index = board::to_index(to_pos.first, to_pos.second + y);

            if (!board::empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

                if (std::abs(y) != std::abs(yy)) {
                    indexes.push_back(index);
                }
            }
        }
    }

    states::state_controller::selected_index_ = index_on;

    states::state_controller::possible_movements_.clear();
    states::state_controller::custom_valid_targets[entity_id].clear();

    used = true;
}

std::string giant_ram::hint() const {

    std::string desc;
    desc = "Giant Ram - the giant will accelerate and attack all units in his path.\n"
            "Damage: " + std::to_string(damage) + ".\n"
            "This ability can be used only once per battle.";

    return std::move(desc);
}