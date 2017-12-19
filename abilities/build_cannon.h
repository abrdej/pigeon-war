//
// Created by abrdej on 20.11.17.
//

#ifndef PIGEONWAR_BUILD_CANNON_H
#define PIGEONWAR_BUILD_CANNON_H

#include <core/turn.h>
#include "abilities/ability.h"

class build_cannon : public ability, turn_events_helper::every_turn_callback_helper {
public:
    build_cannon();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::build_cannon;
    }

    void prepare(size_t for_index) override;
    void use(size_t index_on);

//    static constexpr abilities::ability_types type = abilities::ability_types::special;
//
//    std::string get_bitmap_key() const {
//        return "cannon";
//    }

//    void callback() {
//        auto pos = board::to_pos(states::state_controller::selected_index_);
//        auto pos_to_build = pos;
//        pos_to_build.second += 1;
//
//        states::state_controller::possible_movements_.clear();
//        states::state_controller::possible_movements_.push_back(board::to_index(pos_to_build.first, pos_to_build.second));
//
//        states::state_controller::actual_targeting_type_ = states::target_types::all;
//        states::state_controller::wait_for_action([this](size_t index)
//                                                  {
//                                                      return use(index);
//                                                  });
//    }

private:
    bool built{false};
};


#endif //PIGEONWAR_BUILD_CANNON_H
