#include <core/states.h>
#include <managers/entity_manager.h>
#include <managers/additions_manager.h>
#include "spider_web.h"
#include "damage_dealers.h"

spider_web_slowdown::spider_web_slowdown(float slow_down_to, int slow_last, std::size_t receiver_entity_id) {

    auto& abilities = abilities_manager::component_for(receiver_entity_id);
    moveable_backup =  abilities.type(abilities::ability_types::moving);
    abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(slow_down_to));

    rec = turn::turn_system::every_round([this, slow_down_to, slow_last, receiver_entity_id, counter = 0]() mutable {

        if (entity_manager::alive(receiver_entity_id)) {
            if (++counter == slow_last) {

                auto& ab = abilities_manager::component_for(receiver_entity_id);
                ab.add_ability(abilities::ability_types::moving, moveable_backup);

                rec.reset();
                destroyer();
            }

        } else {
            rec.reset();
            destroyer();
        }
    });
}

spider_web::spider_web(std::size_t entity_id) : entity_id(entity_id) {
    onEveryRound([this]() {
        used = false;
    });
}

void spider_web::prepare(size_t for_index) {

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

void spider_web::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto pos_1 = board::to_pos(used_from_index);
    auto pos_2 = board::to_pos(index_on);

    int x = pos_2.first - pos_1.first;
    int y = pos_2.second - pos_1.second;
    if (x != 0)
        x = x / std::abs(x);
    if (y != 0)
        y = y / std::abs(y);

    auto land_index = board::to_index(pos_1.first + x, pos_1.second + y);

    animation::player<animation::move>::launch
            (animation::move(used_from_index, index_on, typeid(*this)));
    animation::base_player::play();

    auto enemy_id = board::take(index_on);

    if (index_on != land_index) {
        animation::player<animation::move>::launch
                (animation::move(index_on, land_index, typeid(*this)));
        animation::base_player::play();
    }

    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(land_index, std::chrono::milliseconds(150), "spider_web.png"));
    animation::base_player::play();

    board::give_back(enemy_id, land_index);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, enemy_id, entity_id));

    additions_manager::add_component<spider_web_slowdown>(enemy_id, 1, 2, enemy_id);

    used = true;
}