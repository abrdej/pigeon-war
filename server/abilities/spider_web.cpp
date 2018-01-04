#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <managers/additions_manager.h>
#include "spider_web.h"
#include "damage_dealers.h"
#include "jaw_spider.h"
#include "moveable.h"

spider_web::spider_web(std::size_t entity_id) : caster_id(entity_id) {
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

    animations_queue::push_animation(animation_types::move,
                                     used_from_index,
                                     index_on,
                                     -1,
                                     bitmap_key::spider_web);

    auto enemy_id = board::take(index_on);

    if (index_on != land_index) {
        animations_queue::push_animation(animation_types::move,
                                         index_on,
                                         land_index,
                                         -1,
                                         bitmap_key::spider_web);
    }

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     land_index,
                                     150,
                                     -1,
                                     bitmap_key::spider_web);

    board::give_back(enemy_id, land_index);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, enemy_id, caster_id));

    if (entity_manager::alive(enemy_id)) {
        auto& enemy_abilities = abilities_manager::component_for(enemy_id);
        auto moveable_backup =  enemy_abilities.type(abilities::ability_types::moving);
        enemy_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(1));

        auto slow_down_receiver =
                turn::turn_system::every_round([this, slow_last = 2, enemy_id, moveable_backup, counter = 0]() mutable {

                    if (++counter == slow_last) {

                        auto& inner_enemy_abilities = abilities_manager::component_for(enemy_id);
                        inner_enemy_abilities.add_ability(abilities::ability_types::moving, moveable_backup);

                        additions_manager::remove_component(enemy_id,
                                                            "spider_web_effect");
                    }
                });

        additions_manager::add_component(enemy_id, "spider_web_effect", slow_down_receiver);
    }

    used = true;

    auto& caster_abilities = abilities_manager::component_for(caster_id);
    auto jaw_spider_ptr = std::static_pointer_cast<jaw_spider>(caster_abilities.type(abilities::ability_types::offensive));
    jaw_spider_ptr->set_used();
}

void spider_web::set_used() {
    used = true;
}