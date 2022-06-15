#include <components/power_field.h>
#include <managers/entity_manager.h>
#include <messages/massages_makers.h>
#include "vicious_circle.h"
#include "damage_dealers.h"
#include "server/sender.h"

vicious_circle::vicious_circle(std::uint32_t entity_id) : entity_id(entity_id) {
}

void vicious_circle::prepare(std::uint32_t for_index) {
    game_control().selected_index_ = for_index;

    board_helper::circle(for_index, game_control().possible_movements_, false);

    game_control().actual_targeting_type_ = target_types::enemy;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    LOG(debug) << "power: " << power;
}

std::string vicious_circle::hint() const {
    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;
    return "Magic power: " + std::to_string(power);
}

void vicious_circle::use(std::uint32_t index_on) {

    if (used)
        return;

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    auto used_from_index = game_control().selected_index_;
    auto entity_id = game_board().at(used_from_index);

    sender::send(make_action_message("vicious_circle", index_on));

    damage_dealers::standard_damage_dealer(magic_damage(power, game_board().at(index_on), entity_id));

    game::get<entity_manager>().get(entity_id).get<power_filed>()->power = 0;

    used = true;
}