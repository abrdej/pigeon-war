#include "fist_of_doom.h"
#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <server/sender.h>
#include <components/damage_pack.h>
#include <components/applied_effects.h>
#include <messages/make_message.h>
#include "damage_dealers.h"
#include "possible_move_helper.h"

fist_of_doom::fist_of_doom(std::uint32_t entity_id)
        : entity_id(entity_id) {

}

std::string fist_of_doom::hint() const {
    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;
    return "Magic power: " + std::to_string(power);
}

void fist_of_doom::prepare(std::uint32_t for_index) {

    game_control().selected_index_ = for_index;

    board_helper::all(game_control().possible_movements_);

    game_control().actual_targeting_type_ = target_types::enemy;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });
}

void fist_of_doom::use(std::uint32_t index_on) {

    if (used)
        return;

    auto& power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);
    auto enemy_id = game_board().at(index_on);

    auto damage = damage_per_power * power;

    sender::send(make_action_message("fist_of_doom", index_on));

    damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, caster_id));

    power = 0;

    used = true;
}
