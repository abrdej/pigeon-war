//
// Created by abrdej on 20.11.17.
//

#ifndef PIGEONWAR_BUILD_BARRACT_H
#define PIGEONWAR_BUILD_BARRACT_H

#include <abilities/ability.h>
#include <core/turn.h>

class build_barrack : public ability, turn_events_helper::every_turn_callback_helper {
public:
    build_barrack();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::build_barrack;
    }

    void prepare(size_t for_index) override;
    void use(size_t index_on);

private:
    bool built{false};
};


#endif //PIGEONWAR_BUILD_BARRACT_H
