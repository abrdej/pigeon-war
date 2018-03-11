#include <core/states_controller.h>
#include <core/board.h>
#include <components/damage_taker.h>
#include "absorption.h"
#include "damage_dealers.h"

absorption::absorption(std::uint32_t entity_id) : entity_id(entity_id) {

}

absorption::~absorption() {
    if (protected_id != std::numeric_limits<std::uint32_t>::max()) {
        set_damage_receiver(protected_id, protected_dmg_rec_backup);
    }
}

void absorption::prepare(std::uint32_t for_index) {
    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       range);

    states::state_controller::actual_targeting_type_ = target_types::friendly;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });
}

void absorption::use(std::uint32_t index_on) {

    if (used)
        return;

    used = true;
    auto used_from_index = states::state_controller::selected_index_;

    auto friendly_id = board::at(index_on);

    if (protected_id != friendly_id) {

        if (protected_id != std::numeric_limits<std::uint32_t>::max()) {
            set_damage_receiver(protected_id, protected_dmg_rec_backup);
        }

        protected_id = friendly_id;
        protected_dmg_rec_backup = get_damage_receiver(friendly_id);
    }

    set_damage_receiver(friendly_id,
                        [this, friendly_id, dmg_receiver = protected_dmg_rec_backup](health_field& health_pack, const damage_pack& dmg) mutable {

                            auto half_dmg = static_cast<std::int32_t>(dmg.damage_value * 0.5);

                            damage_pack new_dmg = dmg;
                            new_dmg.damage_value = half_dmg;

                            auto damage = dmg_receiver(health_pack, new_dmg);

                            damage_pack last_dmg = dmg;
                            last_dmg.damage_value = dmg.damage_value - half_dmg;
                            last_dmg.damage_receiver_id = entity_id;

                            absorption_power = std::min(absorption_power + last_dmg.damage_value,
                                                        max_absorption_power);

                            std::cout << "absorption_power: " << absorption_power << "\n";

//                            animations_queue::push_animation(animation_types::flash_bitmap,
//                                                             board::index_for(friendly_id),
//                                                             150,
//                                                             0,
//                                                             "absorption);

                            damage_dealers::standard_damage_dealer(last_dmg);

                            return damage;
                        });

    play_animation(used_from_index, index_on);
}

void absorption::play_animation(std::uint32_t from_index, std::uint32_t to_index) {
    //animations_queue::push_animation(animation_types::flash_bitmap, from_index, 150, 0, "absorption);
    //animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, "absorption);
}