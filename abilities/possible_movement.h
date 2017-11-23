////
//// Created by abrdej on 22.11.17.
////
//
//#ifndef PIGEONWAR_POSSIBLE_MOVEMENT_H
//#define PIGEONWAR_POSSIBLE_MOVEMENT_H
//
//#include "core/path_finder.h"
//#include "core/states.h"
//
//struct neighboring_fields_policy {
//    bool available{true};
//    void operator()() const {
//        board_helper::neighboring_fields(states::state_controller::selected_index_,
//                                         states::state_controller::possible_movements_,
//                                         available);
//    }
//};
//
//
//
//struct all_free_policy {
//    void operator()() const {
//        board_helper::all_free(states::state_controller::possible_movements_);
//    }
//};
//
//
//template <typename Policy>
//struct possible_movement : Policy {
//
//    states::target_types target_type{states::target_types::non};
//
//    void set_possible_movements(std::size_t index) {
//        states::state_controller::selected_index_ = index;
//        states::state_controller::actual_targeting_type_ = target_type;
//        (*this)();
//    }
//
//    template <typename Func>
//    void wait_for_action(Func func) {
//        states::state_controller::actual_state_ = states::states_types::wait_for_action;
//        states::state_controller::wait_for_action([func](size_t selected_index)
//                                                  {
//                                                      return func(selected_index);
//                                                  });
//    }
//};
//
//
//#endif //PIGEONWAR_POSSIBLE_MOVEMENT_H
