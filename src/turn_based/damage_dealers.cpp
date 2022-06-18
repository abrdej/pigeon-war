#include <turn_based/damage_dealers.h>

#include <random>

#include <turn_based/components/damage_taker.h>

namespace {

std::int32_t random_damage(std::int32_t damage) {
  std::random_device rd;
  std::default_random_engine dre(rd());
  std::uniform_int_distribution<std::int32_t> uniform_dist(-1, 1);
  std::int32_t random = uniform_dist(dre);
  return damage + random;
}

}  // namespace

std::int32_t damage_dealers::standard_damage_dealer(const damage_pack& dmg) {
  base_entity entity = game::get<entity_manager>().get(dmg.damage_receiver_id);

  auto health_field_ptr = entity.get<health_field>();

  if (!health_field_ptr->is_destructible) {
    return 0;
  }

  damage_pack dmg_copy = dmg;
  dmg_copy.damage_value = random_damage(dmg.damage_value);

  // entity.get<damage_taker>()->receive_damage(dmg_copy);
  auto dealt_damage = game_get<damage_manager>().deal_damage(dmg_copy);

  if (health_field_ptr->health <= 0 && health_field_ptr->is_destructible)
    game::get<entity_manager>().destroy(dmg_copy.damage_receiver_id);

  return dealt_damage;
}

std::int32_t standard_healing(const heal_pack& heal) {
  // return game::get<entity_manager>().get(hl.receiver_id).get<damage_taker>()->heal(hl);
  return game_get<damage_manager>().heal(heal);
}
