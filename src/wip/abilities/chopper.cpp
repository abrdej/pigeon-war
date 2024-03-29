#include <turn_based/game_controller.h>
#include <turn_based/board.h>
#include <wip/entities/creature.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <chopper.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/sender.h>

chopper::chopper(std::uint32_t entity_id) : entity_id(entity_id) {
    on_every_two_turns_from_next([this]() {
        used = false;
    });

    on_every_turn([this, entity_id]() {
        if (fired) {

            auto index = game_board().index_for(entity_id);

            std::vector<std::uint32_t> neighboring;
            board_helper::neighboring_fields(index, neighboring, false);

            for (auto& attack_index : neighboring) {
                if (!game_board().empty(attack_index))
                    damage_dealers::standard_damage_dealer(special_damage(fired_aura_dmg,
                                                                         game_board().at(attack_index),
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

void chopper::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(index_on);

    sender::send(make_action_message("chopper", used_from_index, index_on));

    auto enemy_id = game_board().at(index_on);

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

    auto entity = game::get<entity_manager>().get(entity_id);

    auto spiral_of_fire_ptr = entity.get<abilities>()->get<spiral_of_fire>();
    spiral_of_fire_ptr->can_be_used = true;
}

void chopper::remove_fired() {

    damage = no_fired_damage;
    fired = false;
    last_attacked.clear();
    fired_counter = 0;
}