#include <managers/power_manager.h>
#include <animation/animation.h>
#include "vicious_circle.h"
#include "damage_dealers.h"

vicious_circle::vicious_circle(std::size_t entity_id) : entity_id(entity_id) {
}

void vicious_circle::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;

    board_helper::circle(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });

    auto power = powers_manager::get_power_for(entity_id);

    std::cout << "power: " << power << "\n";
}

void vicious_circle::use(size_t index_on) {

    if (used)
        return;

    auto power = powers_manager::get_power_for(entity_id);

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(index_on);

    damage_dealers::standard_damage_dealer(magic_damage(power, board::at(index_on), entity_id));

    powers_manager::set_power_to(entity_id, 0);

    used = true;
}

void vicious_circle::play_animation(size_t index_on) {
    animations_queue::push_animation(animation_types::flash_bitmap, index_on, 200, -1, bitmap_key::magic_energy);
}