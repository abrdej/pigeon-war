#include <components/applied_effects.h>
#include <messages/make_message.h>
#include "giant_blow.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"

giant_blow::~giant_blow() {
    if (enemy_with_effect != std::numeric_limits<std::uint32_t>::max()) {
        states::state_controller::custom_valid_targets[enemy_with_effect].clear();
        remove_effect(enemy_with_effect,
                      "force to attack a giant");
    }
}

void giant_blow::use(std::uint32_t index_on)
{
    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    sender::send(make_action_message("giant_blow", used_from_index, index_on));

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    ++counter;

    enemy_with_effect = std::numeric_limits<std::uint32_t>::max();

    if (entity_manager::alive(enemy_id)) {

        if (counter == 3) {
            states::state_controller::custom_valid_targets[enemy_id].insert(caster_id);
            states::state_controller::custom_valid_target_type = states::state_controller::custom_target_type::entity_id;

            auto only_target_connection = make_after_n_round_callback_holder(duration_of_giant_only_target,
                                                                                   [enemy_id]() mutable {
                                                                                       states::state_controller::custom_valid_targets[enemy_id].clear();
                                                                                       remove_effect(enemy_id,
                                                                                                     "force to attack a giant");
                                                                                   });

            auto only_target_effect = make_negative_effect("force to attack a giant");
            only_target_effect->set_turn_connection(std::move(only_target_connection));

            add_effect(enemy_id, only_target_effect);

            enemy_with_effect = enemy_id;
        }
    }

    used = true;
}