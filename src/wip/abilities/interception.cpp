#include <interception.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/board.h>
#include <turn_based/path_finder.h>
#include <turn_based/game_controller.h>
#include <components/damage_taker.h>
#include <turn_based/managers/players_manager.h>

interception::interception(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id, counter = 0](health_field& health_pack, const damage_pack& dmg) mutable {

        if (!used) {

            //is_active = false;

            auto index = game_board().index_for(entity_id);

            auto backup_id = game_board().take(index);
            game_board().give_back(backup_id, index);

            damage_accumulated += dmg.damage_value;

            return 0;

        } else {
            auto final_damage = std::min(health_pack.health, dmg.damage_value);
            health_pack.health -= final_damage;

            return final_damage;
        }
    });

    on_every_two_turns_from_next([this, entity_id]() {
        used = false;
    });
}

void interception::prepare(std::uint32_t for_index) {
    game_control().selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, game_control().possible_movements_, false);

    game_control().actual_targeting_type_ = target_types::enemy;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });
}

void interception::use(std::uint32_t index_on) {
    if (used) {
        return;
    }

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);

    play_animation(used_from_index, index_on);

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage + damage_accumulated, enemy_id, caster_id));

    damage_accumulated = 0;

    used = true;
}

void interception::play_animation(std::uint32_t index_from, std::uint32_t index_on) {
    auto entity_id = game_board().take(index_from);

//    animations_queue::push_animation(animation_types::move,
//                                     index_from,
//                                     index_on,
//                                     entity_id,
//                                     "none);
//
//    animations_queue::push_animation(animation_types::flash_bitmap,
//                                     index_on,
//                                     150,
//                                     0,
//                                     "ninja);
//
//    animations_queue::push_animation(animation_types::move,
//                                     index_on,
//                                     index_from,
//                                     entity_id,
//                                     "none);

    game_board().give_back(entity_id, index_from);
}