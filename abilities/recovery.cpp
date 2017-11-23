#include <managers/health_manager.h>
#include <animation/animation.h>
#include <core/board.h>
#include "recovery.h"

recovery::recovery(std::size_t id) : entity_id(id) {

    healths_manager::on_receive_damage(entity_id, [this]() {
        no_damage_counter = 0;
    });

    onEveryRound([this]() {
        ++no_damage_counter;

        auto this_index = board::index_for(entity_id);
        if (last_index == this_index)
            ++no_move_counter;
        else
            no_move_counter = 0;

        if (no_move_counter > required_no_move) {

            auto health_pack = healths_manager::component_for(entity_id);

            //auto final_recovery = std::min<int>(recovery_amount_per_turn,
            //                                   health_pack.base_health - health_pack.health);

            if (recovery_amount_per_turn > 0) {
                healths_manager::receive_damage(entity_id, -recovery_amount_per_turn);

                auto index = board::index_for(entity_id);

                animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index,
                                                                                           std::chrono::milliseconds(
                                                                                                   150),
                                                                                           "healthing.png"));
                animation::base_player::play();
            }
        }

        last_index = this_index;


        if (no_damage_counter > required_no_damage) {


        }
    });
}
