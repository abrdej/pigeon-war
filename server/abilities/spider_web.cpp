#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <managers/additions_manager.h>
#include "spider_web.h"
#include "damage_dealers.h"
#include "jaw_spider.h"
#include "moveable.h"

spider_web::spider_web(sf::Uint64 entity_id) : caster_id(entity_id) {
}

void spider_web::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto pos_1 = board::to_pos(used_from_index);
    auto pos_2 = board::to_pos(index_on);

    sf::Int32 x = pos_2.first - pos_1.first;
    sf::Int32 y = pos_2.second - pos_1.second;
    if (x != 0)
        x = x / std::abs(x);
    if (y != 0)
        y = y / std::abs(y);

    auto land_index = board::to_index(pos_1.first + x, pos_1.second + y);

    sender::send(message_types::animation, animation_def::spider_web, used_from_index, index_on, land_index);

    auto enemy_id = board::at(index_on);

    board::move(index_on, land_index);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, enemy_id, caster_id));

    if (entity_manager::alive(enemy_id)) {
        auto& enemy_abilities = abilities_manager::component_for(enemy_id);
        auto moveable_backup =  enemy_abilities.type(abilities::ability_types::moving);
        enemy_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(1));

        auto slow_down_receiver =
                turn::turn_system::every_turn([this, slow_last = 1, enemy_id, moveable_backup, counter = 0]() mutable {

                    if (counter++ == slow_last * 2) {

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