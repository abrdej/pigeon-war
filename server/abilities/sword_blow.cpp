#include "sword_blow.h"
#include "core/states_controller.h"
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

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    std::vector<size_t> around_fields_ids;
    board_helper::neighboring_fields(used_from_index, around_fields_ids, false);

    play_sword_blow_animation(used_from_index);

    int hit_entities_counter = 0;

    for (auto&& field_id : around_fields_ids) {
        if (!board::empty(field_id)) {
            auto final_damage = damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
            if (final_damage != 0) {
                ++hit_entities_counter;
            }
        }
    }

    if (hit_entities_counter == 3) {
        play_sword_blow_animation(used_from_index);
        for (auto&& field_id : around_fields_ids) {
            if (!board::empty(field_id)) {
                damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
            }
        }
    }

    used = true;
}

void sword_blow::play_sword_blow_animation(size_t from_index) {

    auto entity_id = board::take(from_index);

    auto from_cr = board::to_pos(from_index);
    from_cr.first -= 1;
    from_cr.second -= 1;

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     board::to_index(from_cr.first, from_cr.second),
                                     150,
                                     entity_id,
                                     bitmap_key::samurai_rat_sword);

    board::give_back(entity_id, from_index);
}