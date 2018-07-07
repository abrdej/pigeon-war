#include "charge.h"

#include <messages/make_message.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <core/board.h>
#include <abilities/damage_dealers.h>

charge::charge(std::uint32_t entity_id) {
    after_player_turn(entity_id, [entity_id, this]() {
        if (!used && has_effect(entity_id, "insensitivity")) {

            exhausted = true;

            sender::send(make_action_message("set_discharged", entity_id));

            auto exhausted_connection = make_after_n_round_callback_holder(1,
                                                                           [entity_id, this]() mutable {
                                                                               exhausted = false;
                                                                               sender::send(make_action_message("reaper_no_effect",
                                                                                                                entity_id));
                                                                               remove_effect(entity_id,
                                                                                             "discharged");
                                                                           });

            auto exhausted_effect = make_not_removable_negative_effect("discharged");
            exhausted_effect->set_turn_connection(std::move(exhausted_connection));

            add_effect(entity_id,
                       exhausted_effect);


        }
        used = false;
    });
}

void charge::use(std::uint32_t index_on) {

    if (used || exhausted)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto from_pos = game::get<board>().to_pos(used_from_index);
    auto on_pos = game::get<board>().to_pos(index_on);

    std::int32_t x_diff = from_pos.first - on_pos.first;
    std::int32_t y_diff = from_pos.second - on_pos.second;

    auto x = on_pos.first - x_diff;
    auto y = on_pos.second - y_diff;

    auto index_to = game::get<board>().to_index(x, y);

    if (!game::get<board>().empty(index_to)) {
        return;
    }

    auto entity_id = game::get<board>().at(used_from_index);

    sender::send(make_action_message("charge", used_from_index, index_on, index_to));

    damage_dealers::standard_damage_dealer(melee_damage(damage, game::get<board>().at(index_on), entity_id));

    game::get<board>().move(used_from_index, index_to);

    if (has_effect(entity_id, "insensitivity")) {
        std::cout << "has insensitivity\n";
    } else {
        std::cout << "no insensitivity\n";
    };

    set_destructible(entity_id, false);

    auto insensitivity_connection = make_after_n_turns_callback_holder(3,
                                                                       [entity_id]() mutable {
                                                                           set_destructible(entity_id, true);
                                                                           sender::send(make_action_message("reaper_no_effect", entity_id));
                                                                           remove_effect(entity_id,
                                                                                         "insensitivity");
                                                                       });

    auto insensitivity_effect = make_not_removable_positive_effect("insensitivity");
    insensitivity_effect->set_turn_connection(std::move(insensitivity_connection));

    add_effect(entity_id,
               insensitivity_effect);

    sender::send(make_action_message("set_insensitivity", entity_id));

    states::state_controller::selected_index_ = index_to;
    states::state_controller::possible_movements_.clear();

    used = true;
}