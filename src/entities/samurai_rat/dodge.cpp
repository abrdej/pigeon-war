#include <dodge.h>

#include <turn_based/components/damage_taker.h>

dodge::dodge(std::uint32_t entity_id)
    : passive_ability(name),
      entity_id_(entity_id) {
  set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {
    if (++counter_ == 3) {
      counter_ = 0;
      auto index = game_board().index_for(entity_id);
      sender::send(make_action_message(name, index));
      return 0;

    } else {
      auto final_damage = std::min(health_pack.health, dmg.damage_value);
      health_pack.health -= final_damage;

      return final_damage;
    }
  });

  configure_hint(config_directory + name + ".json", "hint", counter_);

  LOG(debug) << "Dodge setup:";
  LOG(debug) << "entity_id: " << entity_id_;
}
