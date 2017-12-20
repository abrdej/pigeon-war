#include <core/states_controller.h>
#include <core/board.h>
#include "managers/abilities_manager.h"
#include "power_circle.h"
#include "damage_dealers.h"
#include "absorption.h"

power_circle::power_circle(std::size_t entity_id) {

    onEveryTurn([this, entity_id]() {

        if (players::active_player_name() == players::player_for_entity(entity_id)) {

            //for (auto&& dmg_rec_pack : dmg_rec_backup) {
            //    healths_manager::set_damage_receiver(dmg_rec_pack.first, dmg_rec_pack.second);
            //}
            //dmg_rec_backup.clear();

            //damage_reduction = 0;

            auto& abilities = abilities_manager::component_for(entity_id);
            auto absorption_ptr = std::static_pointer_cast<absorption>(abilities.type(abilities::ability_types::special));

            absorption_ptr->zero_dmg_reduction();

            if (absorption_ptr->is_full()) {
                bonus_active = true;
            } else if (bonus_active && ++bonus_counter == max_bonus_counter) {
                bonus_active = false;
                absorption_power = 0;
                bonus_counter = 0;
                absorption_ptr->set_empty();
            }

            std::vector<std::size_t> aim_indexes;
            board_helper::circle(board::index_for(entity_id), aim_indexes, false);

            auto from_cr = board::to_pos(board::index_for(entity_id));
            from_cr.first -= 2;
            from_cr.second -= 2;

            animations_queue::push_animation(animation_types::flash_bitmap,
                                             board::to_index(from_cr.first, from_cr.second),
                                             150,
                                             -1,
                                             bitmap_key::absorber_orbit);

            for (auto& index : aim_indexes) {
                if (!board::empty(index)) {
                    if (players_funcs::enemy_entity(index)) {
                        damage_dealers::standard_damage_dealer(magic_damage(damage, board::at(index), entity_id));

                    } else if (players_funcs::player_entity(index)) {

                        //++damage_reduction;
                        absorption_ptr->increase_dmg_reduction();

                        //auto friendly_id = board::at(index);
                        //auto dmg_rec = healths_manager::get_damage_receiver(friendly_id);

                        //dmg_rec_backup.insert(std::make_pair(friendly_id, dmg_rec));

//                        healths_manager::set_damage_receiver(friendly_id,
//                                                             [this, entity_id, friendly_id](health_field& health_pack, const damage_pack& dmg) mutable {
//
//                                                                 auto half_dmg = static_cast<int>(dmg.damage_value * 0.5);
//
//                                                                 damage_pack new_dmg = dmg;
//                                                                 new_dmg.damage_value = half_dmg;
//
//                                                                 auto damage = dmg_rec_backup.at(friendly_id)(health_pack, new_dmg);
//
//                                                                 damage_pack last_dmg = dmg;
//                                                                 last_dmg.damage_value = dmg.damage_value - half_dmg;
//                                                                 last_dmg.damage_receiver_id = entity_id;
//
//                                                                 absorption_power = std::min(absorption_power + last_dmg.damage_value,
//                                                                                             max_absorption_power);
//
//                                                                 last_dmg.damage_value = std::max(last_dmg.damage_value - damage_reduction, 0);
//
//                                                                 animation::player<animation::flash_bitmap>::launch
//                                                                         (animation::flash_bitmap(board::index_for(friendly_id),
//                                                                                                  std::chrono::milliseconds(150), "absorption.png"));
//                                                                 animation::base_player::play();
//
//                                                                 damage_dealers::standard_damage_dealer(last_dmg);
//
//                                                                 return damage;
//                                                             });

                    }
                }
            }
        }
    });

}

power_circle::~power_circle() {
    //for (auto&& dmg_rec_pack : dmg_rec_backup) {
    //    healths_manager::set_damage_receiver(dmg_rec_pack.first, dmg_rec_pack.second);
    //}
}

void power_circle::prepare(size_t for_index) {


    states::state_controller::selected_index_ = for_index;

    board_helper::circle(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });

}

void power_circle::use(size_t index_on) {
    if (!bonus_active) {
        return;
    }

    //bonus_active = false;
    //bonus_counter = 0;

    auto entity_id = board::at(states::state_controller::selected_index_);

    damage_dealers::standard_damage_dealer(magic_damage(damage, board::at(index_on), entity_id));

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     index_on,
                                     150,
                                     -1,
                                     bitmap_key::absorption);
}

void power_circle::play_animation(size_t index_on) {

}
