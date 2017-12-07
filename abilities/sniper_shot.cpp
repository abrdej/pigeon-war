#include <core/states.h>
#include "sniper_shot.h"
#include "damage_dealers.h"

sniper_shot::sniper_shot() {
    onEveryRound([this]() {
        used = false;
    });
}

void sniper_shot::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void sniper_shot::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(entity_id, used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    auto health_pack = healths_manager::component_for(enemy_id);
    float health_percent = health_pack.health / static_cast<float>(health_pack.base_health) * 100.f;

    std::cout << "health_percent: " << health_percent << "\n";

    int final_damage = damage;

    if (health_percent < 50.f) {
        final_damage += additional_damage;
    }

    damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

    used = true;
}

void sniper_shot::play_animation(std::size_t entity_id, size_t from_index, size_t to_index) {
    animation::player<animation::move>::launch
            (animation::move(from_index, to_index, typeid(*this)));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "sniper_bum.png"));
    animation::base_player::play();
}
