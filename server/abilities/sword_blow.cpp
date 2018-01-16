#include "sword_blow.h"
#include "core/states_controller.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

std::string sword_blow::hint() const {

    std::string desc;
    desc = "Sword Blow - deals damage of: " + std::to_string(damage) + " to all units around the samurai.\n"
            "If the samurai hits minimum tree units he performs an additional blow.";
    return std::move(desc);
}

void sword_blow::use(std::uint64_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    std::vector<std::uint64_t> around_fields_ids;
    board_helper::neighboring_fields(used_from_index, around_fields_ids, false);

    sender::send(message_types::animation, animation_def::sword_blow, used_from_index);

    std::int32_t hit_entities_counter = 0;

    for (auto&& field_id : around_fields_ids) {
        if (!board::empty(field_id)) {
            auto final_damage = damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
            if (final_damage != 0) {
                ++hit_entities_counter;
            }
        }
    }

    if (hit_entities_counter == 3) {

        sender::send(message_types::animation, animation_def::sword_blow, used_from_index);

        for (auto&& field_id : around_fields_ids) {
            if (!board::empty(field_id)) {
                damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(field_id), entity_id));
            }
        }
    }

    used = true;
}