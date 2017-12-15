#include <core/states.h>
#include "warrior_blow.h"
#include "damage_dealers.h"

warrior_blow::warrior_blow() {
    onEveryRound([this]() {
        used = false;
    });
}

void warrior_blow::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void warrior_blow::use(size_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;


    play_animation(used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    auto caster_id = board::at(used_from_index);
    auto health_pack = healths_manager::component_for(caster_id);

    auto missing_health = health_pack.base_health - health_pack.health;

    auto damage_increase_factor = missing_health / 5;

    auto final_damage = damage_increase_factor * damage_per_factor + damage;

    damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

    used = true;
}

void warrior_blow::play_animation(size_t index_from, size_t index_on) {

    auto entity_id = board::take(index_from);
    animation::player<animation::move>::launch(animation::move(index_from, index_on, entity_id));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "warrior_attack.png"));
    animation::base_player::play();
    animation::player<animation::move>::launch(animation::move(index_on, index_from, entity_id));
    animation::base_player::play();
    board::give_back(entity_id, index_from);

}