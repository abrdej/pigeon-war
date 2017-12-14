#include <core/states.h>
#include <managers/additions_manager.h>
#include "shiruken.h"
#include "damage_dealers.h"

shiruken::shiruken() {
    onEveryRound([this]() {
        used = false;
    });
}

void shiruken::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void shiruken::use(size_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    auto death_mark_receiver =
            turn::turn_system::every_round([this, enemy_id, counter = 0, duration = death_mark_duration]() mutable {
                if (++counter == duration) {
                    additions_manager::remove_component(enemy_id,
                                                        "death_mark");
                }
            });

    additions_manager::add_component(enemy_id,
                                     "death_mark",
                                     death_mark_receiver);

    used = true;
}

void shiruken::play_animation(size_t from_index, size_t to_index) {
    animation::player<animation::move>::launch
            (animation::move(from_index, to_index, typeid(*this)));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "shiruken_splash.png"));
    animation::base_player::play();
}