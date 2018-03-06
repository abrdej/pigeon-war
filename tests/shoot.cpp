#include <gtest/gtest.h>
#include <core/states_controller.h>
#include <abilities/shoot.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <entities/wolf.h>
#include <entities/shooter.h>


TEST(shoot_test, PositiveNos) {

//    auto shooter_id = entity_manager::create<shooter>();
//    auto wolf_id = entity_manager::create<wolf>();
//
//    board::insert(0, shooter_id);
//    board::insert(1, wolf_id);
//
//    states::state_controller::selected_index_ = 0;
//
//    auto abilities_ptr = entity_manager::get(shooter_id).get<abilities>();
//
//    auto shoot_ptr = std::static_pointer_cast<shoot>(abilities_ptr->at(1));
//    shoot_ptr->prepare(0);
//
//
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

