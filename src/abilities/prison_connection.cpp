#include <abilities/prison_connection.h>

#include <boost/range/algorithm_ext/erase.hpp>

#include <abilities/damage_dealers.h>
#include <components/applied_effects.h>
#include <core/board.h>

prison_connection::prison_connection(std::uint32_t entity_id)
        : entity_id(entity_id) {}

void prison_connection::use(std::uint32_t index_on) {

    if (used)
        return;

    const auto enemy_id = game_board().at(index_on);
    const auto caster_id = entity_id;

    auto prison_connection_connection =
            make_after_n_round_callback_holder(duration,
                                               [this, enemy_id, caster_id]() {
                                                   remove_effect(enemy_id,
                                                                 "prison_connection");

                                                   if (game::get<entity_manager>().alive(
                                                           caster_id)) {
                                                       boost::remove_erase(entities_with_effect, enemy_id);
                                                   }
                                               });

    auto prison_connection = make_negative_effect("prison_connection");
    prison_connection->set_turn_connection(std::move(prison_connection_connection));
    prison_connection->set_on_destruction([this, caster_id, enemy_id]() {
        if (game::get<entity_manager>().alive(caster_id)) {
            boost::remove_erase(entities_with_effect, enemy_id);
        }
    });

    add_effect(enemy_id, prison_connection);
    entities_with_effect.push_front(enemy_id);

    auto number_of_entities_with_effect = static_cast<std::int32_t>(entities_with_effect.size());

    std::int32_t final_damage = base_damage + number_of_entities_with_effect * damage_per_entities_with_effect;

    sender::send(make_action_message("start_sorcerer_attack", caster_id));

    for (auto entity_with_effect : entities_with_effect) {
        if (game::get<entity_manager>().alive(entity_with_effect)) {

            auto index = game_board().index_for(entity_with_effect);
            sender::send(make_action_message("prison_connection", index));
            damage_dealers::standard_damage_dealer(magic_damage(final_damage, game_board().at(index), caster_id));
        }
    }

    sender::send(make_action_message("end_sorcerer_attack", caster_id));

    used = true;
}
