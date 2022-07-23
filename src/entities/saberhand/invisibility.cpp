#include <invisibility.h>

#include <turn_based/components/damage_taker.h>
#include <turn_based/board.h>
#include <turn_based/messages/massages_makers.h>
#include <turn_based/sender.h>

invisibility::invisibility(std::uint32_t entity_id)
    : caster_target_ability(name),
      entity_id_(entity_id),
      duration_(get_param_or_default("duration", duration_)) {
  configure_hint(config_directory + name + ".json", "hint", duration_);

  LOG(debug) << "Invisibility setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "duration: " << duration_;
}

void invisibility::use(std::uint32_t on_index) {
  if (used_)
    return;

  hide_me();

  invisibility_callback_ = make_after_n_round_callback_holder(duration_, [this, entity_id = entity_id_]() {
    if (game::get<entity_manager>().alive(entity_id)) {
      show_me();
    }
  });

  used_ = true;
}

void invisibility::hide_me() {
  index_ = game_board().index_for(entity_id_);

  sender::send(make_action_message("set_invisibility", entity_id_));

  set_destructible(entity_id_, false);
}

void invisibility::show_me() {
  sender::send(make_action_message("remove_invisibility", entity_id_));

  set_destructible(entity_id_, true);
}
