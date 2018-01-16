#include "entangling.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <managers/entity_manager.h>

//entangling_life_suck::entangling_life_suck() {
//    onEveryRound([this]() {
//        std::int32_t dealed_damage = 0;
//        if (entity_manager::alive(enemy_id)) {
//            dealed_damage = damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, caster_id));
//        }
//
//        if (entity_manager::alive(caster_id)) {
//            auto health_pack = healths_manager::component_for(caster_id);
//            auto final_recovery = dealed_damage;
//
//
//            if (final_recovery > 0) {
//                healths_manager::receive_damage(healing(final_recovery, caster_id));
//
//                auto index = board::index_for(caster_id);
//
//                animations_queue::push_animation(animation_types::flash_bitmap,
//                                                 index,
//                                                 150,
//                                                 0,
//                                                 bitmap_key::healthing);
//            }
//        }
//    });
//}
//
//entangling::entangling(std::uint32_t id) : entity_id(id) {
//    onEveryRound([this]() {
//        used = false;
//    });
//}
//
//void entangling::prepare(std::uint32_t for_index) {
//    states::state_controller::selected_index_ = for_index;
//    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);
//
//    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
//    states::state_controller::wait_for_action([this](std::uint32_t index)
//                                              {
//                                                  return use(index);
//                                              });
//}
//
//void entangling::use(std::uint32_t index_on) {
//
//    auto used_from_index = states::state_controller::selected_index_;
//    auto caster_id = board::at(used_from_index);
//
//    auto entangling_id = entity_manager::create<entangling_instance>();
//    auto active_player_id = players_manager::get_active_player_id();
//    players_manager::add_entity_for_player(active_player_id, entangling_id);
//
//    auto ability = abilities_manager::component_for(entangling_id).at(static_cast<std::int32_t>(abilities::ability_types::passive));
//
//    auto enemy_id = board::at(index_on);
//    auto life_suck = std::static_pointer_cast<entangling_life_suck>(ability);
//    life_suck->set_enemy_id(enemy_id);
//    life_suck->set_caster_id(caster_id);
//
//    board::insert(index_on, entangling_id);
//
//    damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, caster_id));
//}