#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include "managers/additions_manager.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"

void poisoned_missile::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void poisoned_missile::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    auto poison_receiver =
            turn::turn_system::every_turn([this, enemy_id, counter = 0, pl = poison_last]() mutable {

                if (counter++ % 2) {
                    damage_dealers::standard_damage_dealer(special_damage(5, enemy_id));
                    if (counter == pl * 2) {
                        additions_manager::remove_component(enemy_id,
                                                            "poison");
                    }
                }
    });


    additions_manager::add_component(enemy_id,
                                     "poison",
                                     poison_receiver);

    auto& abilities = abilities_manager::component_for(entity_id);
    auto moveable_ptr = std::static_pointer_cast<moveable>(abilities.type(abilities::ability_types::moving));
    moveable_ptr->refresh_range();

    used = true;
}

void poisoned_missile::play_animation(size_t from_index, size_t to_index) {

    animations_queue::push_animation(animation_types::move,
                                     from_index,
                                     to_index,
                                     -1,
                                     bitmap_key::poisoned_missile);

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     to_index,
                                     150,
                                     -1,
                                     bitmap_key::poisoned_missile_splush);
}