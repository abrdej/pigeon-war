#include <core/states.h>
#include <core/board.h>
#include <entities/creature.h>
#include <gui/bitmap_center.h>
#include <managers/abilities_manager.h>
#include <gui/entity_drawer.h>
#include <gui/drawing_manager.h>
#include "chopper.h"
#include "damage_dealers.h"

chopper::chopper(std::size_t entity_id) : entity_id(entity_id) {
    onEveryRound([this]() {
        used = false;
    });

    onEveryTurn([this, entity_id]() {
        if (fired) {

            auto index = board::index_for(entity_id);

            std::vector<size_t> neighboring;
            board_helper::neighboring_fields(index, neighboring, false);

            for (auto& attack_index : neighboring) {
                if (!board::empty(attack_index))
                    damage_dealers::standard_damage_dealer(special_damage(fired_aura_dmg,
                                                                         board::at(attack_index),
                                                                         entity_id));
            }
        }

        if (fired) {
            ++fired_counter;

            if (fired_counter == 5) {
                remove_fired();
            }
        }
    });
}

void chopper::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void chopper::use(size_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(index_on);

    play_animation(used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    last_attacked.push_back(enemy_id);

    if (!fired && last_attacked.size() == 2 &&
            last_attacked[0] != last_attacked[1] ) {
           // last_attacked[1]  != last_attacked[2] &&
            //last_attacked[0] != last_attacked[2]) {
        set_fired();
    }

    used = true;
}

void chopper::play_animation(size_t index_from, size_t index_on) {

    auto entity_id = board::take(index_from);
    animation::player<animation::move>::launch(animation::move(index_from, index_on, entity_id));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "creature_fired.png"));
    animation::base_player::play();
    animation::player<animation::move>::launch(animation::move(index_on, index_from, entity_id));
    animation::base_player::play();
    board::give_back(entity_id, index_from);
}

void chopper::set_fired() {

    auto drawer = drawing_manager::typed_drawer_for<entity_drawer>(entity_id);
    drawer->change_bitmap(bitmap_key::creature_fired);

    damage = fired_damage;
    fired = true;

    auto ability = abilities_manager::component_for(entity_id).type(abilities::ability_types::special);
    std::shared_ptr<spiral_of_fire> spof = std::static_pointer_cast<spiral_of_fire>(ability);
    spof->can_be_used = true;
}

void chopper::remove_fired() {

    auto drawer = drawing_manager::typed_drawer_for<entity_drawer>(entity_id);
    drawer->change_bitmap(bitmap_key::creature);

    damage = no_fired_damage;
    fired = false;
    last_attacked.clear();
    fired_counter = 0;
}