#include <managers/health_manager.h>
#include <core/states.h>
#include "protection_field.h"
#include "damage_dealers.h"

protection_field::protection_field(std::size_t entity_id) {

    onEveryTurn([this, entity_id]() {
        if (players::active_player_name() == players::player_for_entity(entity_id)) {
            is_active = true;
        }
    });

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        if (is_active && !used) {
            is_active = false;
            return 0;

        } else {
            auto final_damage = std::min(health_pack.health, dmg.damage_value);
            health_pack.health -= final_damage;

            return final_damage;
        }
    });
}

void protection_field::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void protection_field::use(size_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    used = true;
}

void protection_field::play_animation(size_t from_index, size_t to_index) {
    animation::base_player::play();
    animation::player<animation::move>::launch
            (animation::move(from_index, to_index, bitmap_key::protection_field));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "field_shoot.png"));
    animation::base_player::play();
}