#include "interception.h"
#include "damage_dealers.h"
#include <core/board.h>
#include <managers/health_manager.h>
#include <core/path_finder.h>
#include <core/states_controller.h>

interception::interception(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id, counter = 0](health_field& health_pack, const damage_pack& dmg) mutable {

        if (!used) {

            //is_active = false;

            auto index = board::index_for(entity_id);

            auto backup_id = board::take(index);
            board::give_back(backup_id, index);

            damage_accumulated += dmg.damage_value;

            return 0;

        } else {
            auto final_damage = std::min(health_pack.health, dmg.damage_value);
            health_pack.health -= final_damage;

            return final_damage;
        }
    });

    onEveryTurn([this, entity_id]() {
        if (players_manager::get_active_player_id() != players_manager::player_for_entity(entity_id)) {
            used = false;
        }
    });
}

void interception::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void interception::use(size_t index_on) {
    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage + damage_accumulated, enemy_id, caster_id));

    damage_accumulated = 0;

    used = true;
}

void interception::play_animation(size_t index_from, size_t index_on) {
    auto entity_id = board::take(index_from);

    animations_queue::push_animation(animation_types::move,
                                     index_from,
                                     index_on,
                                     entity_id,
                                     bitmap_key::none);

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     index_on,
                                     150,
                                     0,
                                     bitmap_key::ninja);

    animations_queue::push_animation(animation_types::move,
                                     index_on,
                                     index_from,
                                     entity_id,
                                     bitmap_key::none);

    board::give_back(entity_id, index_from);
}