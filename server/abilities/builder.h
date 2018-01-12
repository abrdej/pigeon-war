//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_BUILDABLE_H
#define PIGEONWAR_BUILDABLE_H

#include <server/abilities/ability.h>
#include <core/turn.h>
#include <core/states_controller.h>
#include <core/board.h>
#include <managers/entity_manager.h>

template <typename T>
class builder : public ability, turn_events_helper::every_turn_callback_helper {
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::none;
    }

    builder() {
        onEveryRound([this]() {
            built = false;
        });
    }

//    static constexpr abilities::ability_types type = abilities::ability_types::defensive;
//
//    std::string get_bitmap_key() const {
//        return "barrack";
//    }
//
//    void callback() {
//        auto pos = board::to_pos(states::state_controller::selected_index_);
//        auto pos_to_build = pos;
//        pos_to_build.second += 1;
//
//        states::state_controller::possible_movements_.clear();
//        states::state_controller::possible_movements_.push_back(board::to_index(pos_to_build.first, pos_to_build.second));
//
//        states::state_controller::actual_targeting_type_ = states::target_types::all;
//        states::state_controller::wait_for_action([this](sf::Uint64 index)
//                                                  {
//                                                      return use(index);
//                                                  });
//    }

    void prepare(sf::Uint64 for_index) override {
        states::state_controller::selected_index_ = for_index;

        auto pos = board::to_pos(for_index);
        auto pos_to_build = pos;
        pos_to_build.second += 1;

        states::state_controller::possible_movements_.clear();
        states::state_controller::possible_movements_.push_back(board::to_index(pos_to_build.first, pos_to_build.second));

        states::state_controller::actual_targeting_type_ = states::target_types::all;
        states::state_controller::wait_for_action([this](sf::Uint64 index)
                                                  {
                                                      return use(index);
                                                  });
    }
    void use(sf::Uint64 index_on) {
        if (built)
            return;

        auto entity_id = entity_manager::create<T>();
        auto player_id = players_manager::get_active_player_id();

        players_manager::add_entity_for_player(player_id, entity_id);

        board::insert(index_on, entity_id);

        built = true;
    }

private:
    bool built{false};
};

#endif //PIGEONWAR_BUILDABLE_H
