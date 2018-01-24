#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <components/additions.h>
#include "spider_web.h"
#include "damage_dealers.h"
#include "jaw_spider.h"
#include "moveable.h"
#include "sender.h"
#include "common/animations.h"

spider_web::spider_web(std::uint32_t entity_id) : caster_id(entity_id) {
}

void spider_web::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto pos_1 = board::to_pos(used_from_index);
    auto pos_2 = board::to_pos(index_on);

    std::int32_t x = pos_2.first - pos_1.first;
    std::int32_t y = pos_2.second - pos_1.second;
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

        auto enemy_abilities_ptr = entity_manager::get(enemy_id).get<abilities>();
        auto moveable_base_ptr = std::dynamic_pointer_cast<moveable_base>(enemy_abilities_ptr->type(abilities::ability_types::moving));
        if (moveable_base_ptr) {
            moveable_base_ptr->set_slow_down(1);

            auto slow_down_receiver = make_after_n_turns_callback_holder(duration,
                                                                         [enemy_id, moveable_base_ptr]() mutable {
                                                                             moveable_base_ptr->remove_slow_down();
                                                                             remove_component(enemy_id, "spider_web_effect");
                                                                         });

            add_component(enemy_id, "spider_web_effect", slow_down_receiver);
        }
    }

    used = true;

    auto caster_abilities_ptr = entity_manager::get(caster_id).get<abilities>();
    auto jaw_spider_ptr = std::static_pointer_cast<jaw_spider>(caster_abilities_ptr->type(abilities::ability_types::offensive));
    jaw_spider_ptr->set_used();
}

void spider_web::set_used() {
    used = true;
}