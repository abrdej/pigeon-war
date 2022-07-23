#include <drain.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/components/damage_taker.h>

drain::drain(std::uint32_t entity_id)
    : neighboring_target_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)),
      drain_amount_(get_param_or_default("drain_amount", drain_amount_)) {

  configure_hint(config_directory + name + ".json", "hint", damage_, drain_amount_);

  LOG(debug) << "Drain setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
  LOG(debug) << "drain_amount: " << drain_amount_;
}

void drain::use(std::uint32_t index_on) {
  if (used) {
    return;
  }

  sender::send(make_action_message(name, entity_id_, index_on));

  damage_dealers::standard_damage_dealer(
      damage_pack(damage_, damage_types::MELEE, game_board().at(index_on), entity_id_));

  standard_healing(healing_above_base_health(drain_amount_, entity_id_));

  used = true;
}
