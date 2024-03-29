#include <turn_based/game_controller.h>
#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>
#include <power_circle.h>
#include <turn_based/damage_dealers.h>
#include <absorption.h>
#include <turn_based/abilities.h>

power_circle::power_circle(std::uint32_t entity_id) {

    on_every_two_turns_from_this([this, entity_id]() {


        //for (auto&& dmg_rec_pack : dmg_rec_backup) {
        //    set_damage_receiver(dmg_rec_pack.first, dmg_rec_pack.second);
        //}
        //dmg_rec_backup.clear();

        //damage_reduction = 0;

        auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
        auto absorption_ptr = abilities_ptr->get<absorption>();

        absorption_ptr->zero_dmg_reduction();

        if (absorption_ptr->is_full()) {
            bonus_active = true;
        } else if (bonus_active && ++bonus_counter == max_bonus_counter) {
            bonus_active = false;
            absorption_power = 0;
            bonus_counter = 0;
            absorption_ptr->set_empty();
        }

        std::vector<std::uint32_t> aim_indexes;
        board_helper::circle(game_board().index_for(entity_id), aim_indexes, false);

        auto from_cr = game_board().to_pos(game_board().index_for(entity_id));
        from_cr.first -= 2;
        from_cr.second -= 2;

//        animations_queue::push_animation(animation_types::flash_bitmap,
//                                         game_board().to_index(from_cr.first, from_cr.second),
//                                         150,
//                                         -1,
//                                         "absorber_orbit);

        for (auto& index : aim_indexes) {
            if (!game_board().empty(index)) {
                if (players_helpers::is_enemy_entity(index)) {
                    damage_dealers::standard_damage_dealer(magic_damage(damage, game_board().at(index), entity_id));

                } else if (players_helpers::is_player_entity(index)) {

                    //++damage_reduction;
                    absorption_ptr->increase_dmg_reduction();

                    //auto friendly_id = game_board().at(index);
                    //auto dmg_rec = get_damage_receiver(friendly_id);

                    //dmg_rec_backup.insert(std::make_pair(friendly_id, dmg_rec));

//                        set_damage_receiver(friendly_id,
//                                                             [this, entity_id, friendly_id](health_field& health_pack, const damage_pack& dmg) mutable {
//
//                                                                 auto half_dmg = static_cast<std::int32_t>(dmg.damage_value * 0.5);
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
//                                                                         (animation::flash_bitmap(game_board().index_for(friendly_id),
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
    });

}

power_circle::~power_circle() {
    //for (auto&& dmg_rec_pack : dmg_rec_backup) {
    //    set_damage_receiver(dmg_rec_pack.first, dmg_rec_pack.second);
    //}
}

void power_circle::prepare(std::uint32_t for_index) {


    game_control().selected_index_ = for_index;

    board_helper::circle(for_index, game_control().possible_movements_, false);

    game_control().actual_targeting_type_ = target_types::enemy;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });

}

void power_circle::use(std::uint32_t index_on) {
    if (!bonus_active) {
        return;
    }

    //bonus_active = false;
    //bonus_counter = 0;

    auto entity_id = game_board().at(game_control().selected_index_);

    damage_dealers::standard_damage_dealer(magic_damage(damage, game_board().at(index_on), entity_id));

//    animations_queue::push_animation(animation_types::flash_bitmap,
//                                     index_on,
//                                     150,
//                                     -1,
//                                     "absorption);
}

void power_circle::play_animation(std::uint32_t index_on) {

}
