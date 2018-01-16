#include <core/animations_queue.h>
#include <sender.h>
#include "damage_taker.h"

void play_change_health_animation(std::uint64_t to_index, std::int32_t change_health)
{
    animations_queue::push_animation(animation_types::change_health,
                                     to_index,
                                     change_health,
                                     0,
                                     bitmap_key::none);
    animations_queue::pull();

    sender::send(message_types::healths, get_healths());
}


std::unordered_map<std::uint64_t, std::int32_t> get_healths() {
    std::unordered_map<std::uint64_t, std::int32_t> returned_map;
    entity_manager::for_all([&returned_map](base_entity entity) {
        returned_map.insert(std::make_pair(entity.entity_id, entity.get<health_field>()->health));
    });
    return std::move(returned_map);
}