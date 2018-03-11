#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <common/make_message.h>
#include "sniper_shot.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"
#include "managers/players_manager.h"

void sniper_shot::prepare(std::uint32_t for_index) {

    states::state_controller::selected_index_ = for_index;

    bool enemy_close = false;

    std::vector<std::uint32_t> neighbors;
    board_helper::neighboring_fields(for_index, neighbors, false);
    for (auto& neighbor_index : neighbors)
    {
        if (!board::empty(neighbor_index) && players_funcs::enemy_entity(neighbor_index)) {
            enemy_close = true;
            break;
        }
    }

    if (!enemy_close) {
        board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                    states::state_controller::possible_movements_costs_,
                                    range);

    } else {
        states::state_controller::possible_movements_.clear();
        states::state_controller::possible_movements_costs_.clear();
    }

    states::state_controller::actual_targeting_type_ = target_types::enemy;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });
}

void sniper_shot::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(make_action_message("sniper_shot", used_from_index, index_on));

    auto enemy_id = board::at(index_on);

    auto health_pack = entity_manager::get(enemy_id).get<health_field>();
    float health_percent = health_pack->health / static_cast<float>(health_pack->base_health) * 100.f;

    std::cout << "health_percent: " << health_percent << "\n";

    std::int32_t final_damage = damage;

    if (health_percent < 50.f) {
        final_damage += additional_damage;
    }

    damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

    used = true;
}

std::string sniper_shot::hint() const {

    std::string desc;
    desc = "Sniper Shot - deals damage of: " + std::to_string(damage) + ".\n"
            "If the target is below 50% of health deals additional: " + std::to_string(damage) + " damage.\n"
            "Sniper can't give a shot when the enemy unit is in his neighborhood.\n";
            "Range: " + std::to_string(range) + ".";

    return std::move(desc);
}