#include <sender.h>
#include <common/animations.h>
#include <common/make_message.h>
#include "damage_taker.h"

void play_change_health_animation(std::uint32_t to_index, std::int32_t change_health) {
    sender::send(make_animation_message("change_health", to_index, change_health));
    sender::send(make_entities_healths_message(get_healths()));
}

void play_power_change_animation(std::uint32_t to_index, std::int32_t change_power) {
    sender::send(make_animation_message("change_power", to_index, change_power));
//    sender::send(make_entities_healths_message(get_healths()));
}

std::unordered_map<std::uint32_t, std::int32_t> get_healths() {
    std::unordered_map<std::uint32_t, std::int32_t> returned_map;
    entity_manager::for_all([&returned_map](base_entity entity) {
        returned_map.insert(std::make_pair(entity.entity_id, entity.get<health_field>()->health));
    });
    return std::move(returned_map);
}