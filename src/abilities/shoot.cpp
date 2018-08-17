#include "shoot.h"

#include <abilities/damage_dealers.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <core/path_finder.h>
#include <messages/make_message.h>
#include <server/sender.h>
#include <utils/descriptions.h>

shoot::shoot(std::uint32_t entity_id) : entity_id(entity_id), bullets(bullets_per_turn) {
    on_every_two_turns_from_next([this]() {
        bullets = bullets_per_turn;
    });
}

void shoot::use(std::uint32_t on_index) {
    if (bullets == 0) {
        return;
    }
    --bullets;

    sender::send(make_action_message("shoot", game_control().selected_index_, on_index));
    damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(on_index), entity_id));
}