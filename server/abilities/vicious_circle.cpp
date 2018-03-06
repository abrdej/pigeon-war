#include <components/power_field.h>
#include <animation/animation.h>
#include <managers/entity_manager.h>
#include <common/make_message.h>
#include "vicious_circle.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

vicious_circle::vicious_circle(std::uint32_t entity_id) : entity_id(entity_id) {
}

void vicious_circle::prepare(std::uint32_t for_index) {
    states::state_controller::selected_index_ = for_index;

    board_helper::circle(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = target_types::enemy;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });

    auto power = entity_manager::get(entity_id).get<power_filed>()->power;

    std::cout << "power: " << power << "\n";
}

std::string vicious_circle::hint() const {
    auto power = entity_manager::get(entity_id).get<power_filed>()->power;
    return "Magic power: " + std::to_string(power);
}

void vicious_circle::use(std::uint32_t index_on) {

    if (used)
        return;

    auto power = entity_manager::get(entity_id).get<power_filed>()->power;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(make_animation_message("vicious_circle", index_on));

    damage_dealers::standard_damage_dealer(magic_damage(power, board::at(index_on), entity_id));

    entity_manager::get(entity_id).get<power_filed>()->power = 0;

    used = true;
}