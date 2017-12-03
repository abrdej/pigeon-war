#include <core/states.h>
#include <animation/animation.h>
#include <managers/entity_manager.h>
#include "managers/additions_manager.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"

poisoned_missile_callback::poisoned_missile_callback(int poison_damage, int poison_last, std::size_t receiver_entity_id) {

    rec = turn::turn_system::every_round([this, poison_damage, poison_last, receiver_entity_id, counter = 0]() mutable {
        if (entity_manager::alive(receiver_entity_id)) {
            damage_dealers::standard_damage_dealer(special_damage(poison_damage, receiver_entity_id));

            if (++counter == poison_last) {
                rec.reset();
                destroyer();
            }

        } else {
            rec.reset();
            destroyer();
        }
    });
}

poisoned_missile::poisoned_missile() {
    onEveryRound([this]() {
        used = false;
    });
}

void poisoned_missile::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       range_);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void poisoned_missile::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage_, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    additions_manager::add_component<poisoned_missile_callback>(enemy_id, poison_power_, poison_last_, enemy_id);

    used = true;
}

void poisoned_missile::play_animation(size_t from_index, size_t to_index) {
    //animation::player<animation::flash_bitmap>::launch
    //        (animation::flash_bitmap(from_index, std::chrono::milliseconds(50), "shoot.png"));
    //animation::base_player::play();
    animation::player<animation::move>::launch
            (animation::move(from_index, to_index, typeid(*this)));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "poisoned_missile_splush.png"));
    animation::base_player::play();
}