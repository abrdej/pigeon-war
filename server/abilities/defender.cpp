#include <core/path_finder.h>
#include <core/board.h>
#include <core/animations_queue.h>
#include <components/damage_taker.h>
#include "defender.h"
#include "damage_dealers.h"

defender::defender(std::uint32_t entity_id) {
//    onEveryTurn([this, entity_id]() {
//
//        if (players_manager::get_active_player_id() == players_manager::player_for_entity(entity_id)) {
//
//            std::vector<std::uint32_t> neighbors;
//            board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);
//            for (auto& index : neighbors)
//            {
//                if (!board::empty(index) && players_funcs::player_entity(index)) {
//
//                    animations_queue::push_animation(animation_types::flash_bitmap,
//                                                     index,
//                                                     150,
//                                                     0,
//                                                     bitmap_key::defender);
//
//                    auto protected_id = board::at(index);
//
//                    auto callback_id = on_receive_damage(protected_id, [this, entity_id](const damage_pack& dmg) {
//
//                        auto enemy_index = board::index_for(dmg.damage_dealer_id);
//
//                        animations_queue::push_animation(animation_types::flash_bitmap,
//                                                         enemy_index,
//                                                         100,
//                                                         0,
//                                                         bitmap_key::defender);
//                        animations_queue::push_animation(animation_types::flash_bitmap,
//                                                         enemy_index,
//                                                         150,
//                                                         0,
//                                                         bitmap_key::defender_attack);
//
//                        damage_dealers::standard_damage_dealer(magic_damage(damage, dmg.damage_dealer_id, entity_id));
//
//                    }, damage_taker::on_receive_damage_policy::after);
//
//                    callbacks_ids.emplace_back(protected_id, callback_id);
//                }
//            }
//        } else {
//            for (auto&& callback_pack : callbacks_ids) {
//                remove_on_receive_damage(callback_pack.first, callback_pack.second);
//            }
//            callbacks_ids.clear();
//        }
//    });
}

void defender::prepare(std::uint32_t for_index) {

}

void defender::use(std::uint32_t index_on) {

}