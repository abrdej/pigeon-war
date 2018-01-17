#include <core/animations_queue.h>
#include <sender.h>
#include "damage_taker.h"

void play_change_health_animation(std::uint32_t to_index, std::int32_t change_health)
{
    sender::send(message_types::animation, animation_def::change_health, to_index, change_health);

    sender::send(message_types::healths, get_healths());
}


std::unordered_map<std::uint32_t, std::int32_t> get_healths() {
    std::unordered_map<std::uint32_t, std::int32_t> returned_map;
    entity_manager::for_all([&returned_map](base_entity entity) {
        returned_map.insert(std::make_pair(entity.entity_id, entity.get<health_field>()->health));
    });
    return std::move(returned_map);
}