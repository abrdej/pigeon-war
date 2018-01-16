#include <core/states_controller.h>
#include <core/board.h>
#include <entities/creature.h>
#include <gui/bitmap_center.h>
#include <managers/abilities_manager.h>
#include <gui/entity_drawer.h>
#include <gui/drawing_manager.h>
#include "chopper.h"
#include "damage_dealers.h"

chopper::chopper(sf::Uint64 entity_id) : entity_id(entity_id) {
    onEveryRound([this]() {
        used = false;
    });

    onEveryTurn([this, entity_id]() {
        if (fired) {

            auto index = board::index_for(entity_id);

            std::vector<sf::Uint64> neighboring;
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

void chopper::use(sf::Uint64 index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(index_on);

    sender::send(message_types::animation, animation_def::chopper, used_from_index, index_on);

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

void chopper::set_fired() {

    damage = fired_damage;
    fired = true;

    auto ability = abilities_manager::component_for(entity_id).type(abilities::ability_types::special);
    std::shared_ptr<spiral_of_fire> spof = std::static_pointer_cast<spiral_of_fire>(ability);
    spof->can_be_used = true;
}

void chopper::remove_fired() {

    damage = no_fired_damage;
    fired = false;
    last_attacked.clear();
    fired_counter = 0;
}