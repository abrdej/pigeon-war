#include <components/additions.h>
#include "giant_blow.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

void giant_blow::use(std::uint32_t index_on)
{
    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::giant_blow, used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    if (entity_manager::alive(enemy_id)) {

        if (counter++ == 2) {
            states::state_controller::custom_valid_targets[enemy_id].insert(caster_id);
            states::state_controller::custom_valid_target_type = states::state_controller::custom_target_type::entity_id;

            auto giant_only_target = make_after_n_round_callback_holder(duration_of_giant_only_target,
                                                                        [enemy_id]() mutable {

                                                                            states::state_controller::custom_valid_targets[enemy_id].clear();
                                                                            remove_component(enemy_id,
                                                                                             "giant_only_target");
                                                                        });

            add_component(enemy_id, "giant_only_target", giant_only_target);
        }
    }

    used = true;
}

std::string giant_blow::hint() const {

    std::string desc;
    desc = "Giant Blow - deals damage of " + std::to_string(damage) + ".\n"
            "Every third attack additionally causes that the enemy can attack\n"
            "only the giant for one turn.\n";

    return std::move(desc);
}