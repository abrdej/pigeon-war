#include <animation/animation.h>
#include "managers/types_manager.h"
#include "sword_blow.h"
#include "core/states.h"
#include "damage_dealers.h"

sword_blow::sword_blow() {
    onEveryRound([this]() {
        used = false;
    });
}

void sword_blow::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    states::state_controller::selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void sword_blow::use(size_t index_on) {

    if (used)
        return;

    //audio::shoot_sound();

    auto used_from_index = states::state_controller::selected_index_;

    std::vector<size_t> around_fields_ids;
    board_helper::neighboring_fields(used_from_index, around_fields_ids, false);

    play_sword_blow_animation(used_from_index);

    int hit_entities_counter = 0;

    for (auto&& field_id : around_fields_ids) {
        if (!board::empty(field_id)) {
            auto damage = damage_dealers::standard_damage_dealer(damage_, board::at(field_id));
            if (damage != 0) {
                ++hit_entities_counter;
            }
        }
    }

    if (hit_entities_counter == 3) {
        play_sword_blow_animation(used_from_index);
        for (auto&& field_id : around_fields_ids) {
            if (!board::empty(field_id)) {
                damage_dealers::standard_damage_dealer(damage_, board::at(field_id));
            }
        }
    }

    used = true;
}

void sword_blow::play_sword_blow_animation(size_t from_index) {

    auto entity_id = board::take(from_index);
    auto type = types_manager::component_for(entity_id);
//    animation::player<animation::move>::launch(animation::move(index_from, index_on, type));
//    animation::base_player::play();

    auto from_cr = board::to_pos(from_index);
    from_cr.first -= 1;
    from_cr.second -= 1;

    animation::player<animation::flash_bitmap>::launch(
            animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
                                    std::chrono::milliseconds(150),
                                    "samurai_rat_sword.png"));
    animation::base_player::play();
//    animation::player<animation::move>::launch(animation::move(index_on, index_from, type));
//    animation::base_player::play();
    board::give_back(entity_id, from_index);

}