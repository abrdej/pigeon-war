#include <core/states.h>
#include <animation/animation.h>
#include "poisoned_missile.h"
#include "damage_dealers.h"


poisoned_missile::poisoned_missile() {
    onEveryTurn([this](){
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

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(damage_, index_on);

    auto enemy_id = board::at(index_on);

    static int p_id = 0;

    auto receiver = std::make_shared<std::function<void()>>([id = p_id, this, enemy_id, counter = 0]() mutable {
        auto index = board::index_for(enemy_id);
        damage_dealers::standard_damage_dealer(poison_power_, index);
        if (++counter == poison_last_) {
            rec[id].reset();
        }
    });
    rec[p_id] = receiver;
    turn::turn_system::every_turn(receiver);

    p_id++;

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
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
    animation::base_player::play();
}