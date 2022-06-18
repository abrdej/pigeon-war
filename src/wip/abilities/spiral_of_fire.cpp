#include <turn_based/game_controller.h>
#include <turn_based/board.h>
#include <wip/entities/creature.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <spiral_of_fire.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/sender.h>

spiral_of_fire::spiral_of_fire() {

}

void spiral_of_fire::use(std::uint32_t index_on) {

    if (!can_be_used)
        return;

    auto used_from_index = game_control().selected_index_;
    auto entity_id = game_board().at(used_from_index);

    auto from_pos = game_board().to_pos(index_on);
    auto to_pos = game_board().to_pos(used_from_index);

    std::int32_t xx = static_cast<std::int32_t>(from_pos.first) - static_cast<std::int32_t>(to_pos.first);
    std::int32_t yy = static_cast<std::int32_t>(from_pos.second) - static_cast<std::int32_t>(to_pos.second);

    auto index_to_move = game_board().to_index(to_pos.first + xx, to_pos.second + yy);

    sender::send(make_action_message("spiral_of_fire", used_from_index, index_to_move));

    std::vector<std::uint32_t> indexes;

    if (xx != 0) {
        for (std::int32_t x = xx > 0 ? 1 : -1; std::abs(x) <= std::abs(xx); x = xx > 0 ? x + 1 : x - 1) {

            auto index = game_board().to_index(to_pos.first + x, to_pos.second);

            if (!game_board().empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, game_board().at(index), entity_id));

                if (std::abs(x) != std::abs(xx)) {
                    indexes.push_back(index);
                }
            }
        }
    } else {
        for (std::int32_t y = yy > 0 ? 1 : -1; abs(y) <= abs(yy); y = yy > 0 ? y + 1 : y - 1) {

            auto index = game_board().to_index(to_pos.first, to_pos.second + y);

            if (!game_board().empty(index)) {
                damage_dealers::standard_damage_dealer(special_damage(damage, game_board().at(index), entity_id));

                if (std::abs(y) != std::abs(yy)) {
                    indexes.push_back(index);
                }
            }
        }
    }

    for (std::int32_t i = indexes.size() - 1; i >= 0; --i) {
        if (!game_board().empty(indexes[i])) {
            damage_dealers::standard_damage_dealer(special_damage(damage, game_board().at(indexes[i]), entity_id));
        }
    }
    can_be_used = false;

    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    std::shared_ptr<chopper> chopper_ptr = abilities_ptr->get<chopper>();
    chopper_ptr->remove_fired();
}