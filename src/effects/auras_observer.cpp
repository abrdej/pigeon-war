#include <effects/auras_observer.h>

auras_observer::auras_observer() {
    game_board().on_change([]() {
        game::get<auras_observer>().observe();
    });
}

void auras_observer::add_aura(std::uint32_t for_entity, const std::shared_ptr<effect>& aura) {
    auras.emplace(for_entity, aura);
}

void auras_observer::remove_aura(std::uint32_t from_entity) {
    auras.erase(from_entity);
}

void auras_observer::observe() {
    std::vector<bool> entities_to_remove_aura(entities_with_auras.size(), true);

    for (auto&& entity_with_aura_pack : entities_with_auras) {
        entity_with_aura_pack.second->remove_effect(entity_with_aura_pack.first);
    }
    entities_with_auras.clear();

    std::vector<std::uint32_t> to_remove;

    for (auto&& aura_pack : auras) {
        if (game::get<entity_manager>().alive(aura_pack.first)) {
            auto board_index = game_board().index_for(aura_pack.first);

            std::vector<std::uint32_t> neighbors;
            board_helper::neighboring_fields(board_index, neighbors, false);

            for (auto&& neighbour_index : neighbors) {
                if (!game_board().empty(neighbour_index)) {

                    auto entity_id = game_board().at(neighbour_index);
                    if (aura_pack.second->set_effect(entity_id)) {
                        entities_with_auras.emplace_back(game_board().at(neighbour_index), aura_pack.second);
                    }
                }
            }
        } else {
            to_remove.push_back(aura_pack.first);
        }
    }
    for (auto&& entity_id : to_remove) {
        auras.erase(entity_id);
    }
}
