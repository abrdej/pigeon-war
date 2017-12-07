#include <core/states.h>
#include "magic_bullet.h"
#include "damage_dealers.h"

magic_bullet::magic_bullet(std::size_t entity_id) {
    onEveryTurn([this, entity_id]() {

        if (players::active_player_name() == players::player_for_entity(entity_id)) {
            used = false;
            magic_power += magic_power_accumulation_amount;

            std::vector<size_t> neighbors;
            board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);
            for (auto& index : neighbors)
            {
                if (!board::empty(index) && players_funcs::enemy_entity(index)) {
                    magic_power += magic_power_accumulation_amount;
                    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "magic_suck.png"));
                    animation::base_player::play();
                }
            }
        }
    });

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto damage_for_magic_power = std::min<int>(static_cast<int>(0.5 * magic_power), dmg.damage_value);
        magic_power -= damage_for_magic_power;

        auto remaining_damage = dmg.damage_value - damage_for_magic_power;

        auto final_damage = std::min(health_pack.health, remaining_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

void magic_bullet::prepare(size_t for_index) {

    std::cout << "magic power: " << magic_power << "\n";

    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void magic_bullet::use(size_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(magic_power, board::at(index_on), entity_id));

    magic_power = 0;

    used = true;
}

void magic_bullet::play_animation(size_t from_index, size_t to_index) {
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(from_index, std::chrono::milliseconds(100), "monk_use_1.png"));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(from_index, std::chrono::milliseconds(100), "monk_use_2.png"));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(from_index, std::chrono::milliseconds(100), "monk_use_3.png"));
    animation::base_player::play();
    //animation::player<animation::move>::launch
    //        (animation::move(from_index, to_index, typeid(*this)));
    //animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "magic_splash.png"));
    animation::base_player::play();
}