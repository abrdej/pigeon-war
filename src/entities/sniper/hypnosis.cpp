#include <hypnosis.h>
#include <turn_based/abilities.h>
#include <turn_based/board.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>
#include <turn_based/turn_system.h>

hypnosis::hypnosis(entity_id_t entity_id)
    : path_target_ability(name, range, target_types::enemy, true),
    duration_(get_param_or_default("duration", duration_)) {
  configure_hint(config_directory + name + ".json", "hint");
}

void hypnosis::use(std::uint32_t index_on) {
  if (used_)
    return;

  sender::send(make_action_message(name, index_on));

  auto enemy_id = game_board().at(index_on);

  auto enemy_abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();
  enemy_abilities_ptr->is_active = false;

  auto hypnosis_connection = make_after_n_round_callback_holder(duration_, [enemy_id]() mutable {

    auto inner_enemy_abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();
    inner_enemy_abilities_ptr->is_active = true;

    remove_effect(enemy_id, "hypnotised");
  });

  auto hypnosis_effect = make_negative_effect("hypnotised");
  hypnosis_effect->set_turn_connection(std::move(hypnosis_connection));

  add_effect(enemy_id, hypnosis_effect);

  used_ = true;
}