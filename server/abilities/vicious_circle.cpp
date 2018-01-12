#include <managers/power_manager.h>
#include <animation/animation.h>
#include "vicious_circle.h"
#include "damage_dealers.h"

vicious_circle::vicious_circle(sf::Uint64 entity_id) : entity_id(entity_id) {
}

void vicious_circle::prepare(sf::Uint64 for_index) {
    states::state_controller::selected_index_ = for_index;

    board_helper::circle(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](sf::Uint64 index)
                                              {
                                                  return use(index);
                                              });

    auto power = powers_manager::get_power_for(entity_id);

    std::cout << "power: " << power << "\n";
}

std::string vicious_circle::hint() const {
    auto power = powers_manager::get_power_for(entity_id);
    return "Magic power: " + std::to_string(power);
}

void vicious_circle::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto power = powers_manager::get_power_for(entity_id);

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::vicious_circle, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(power, board::at(index_on), entity_id));

    powers_manager::set_power_to(entity_id, 0);

    used = true;
}