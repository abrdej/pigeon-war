#include <turn_based/board.h>
#include <recovery.h>

recovery::recovery(std::uint32_t id) : entity_id(id) {

//    on_receive_damage(entity_id, [this](const damage_pack&) {
//        no_damage_counter = 0;
//    }, on_receive_damage_policy::after);
//
//    onEveryRound([this]() {
//        ++no_damage_counter;
//
//        auto this_index = game_board().index_for(entity_id);
//        if (last_index == this_index)
//            ++no_move_counter;
//        else
//            no_move_counter = 0;
//
//        if (no_move_counter > required_no_move) {
//
//            auto health_pack = healths_manager::component_for(entity_id);
//
//            //auto final_recovery = std::min<std::int32_t>(recovery_amount_per_turn,
//            //                                   health_pack.base_health - health_pack.health);
//
//            if (recovery_amount_per_turn > 0) {
//                healths_manager::receive_damage(damage_pack(-recovery_amount_per_turn,
//                                                            damage_types::UNDEFINED,
//                                                            entity_id));
//
//                auto index = game_board().index_for(entity_id);
//
//                animations_queue::push_animation(animation_types::flash_bitmap,
//                                                 index,
//                                                 150,
//                                                 -1,
//                                                 "healthing);
//            }
//        }
//
//        last_index = this_index;
//
//
//        if (no_damage_counter > required_no_damage) {
//
//
//        }
//    });
}
