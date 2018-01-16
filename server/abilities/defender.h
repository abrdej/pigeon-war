//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_DEFENDER_H
#define PIGEONWAR_DEFENDER_H

#include "ability.h"
#include "core/turn_system.h"

class defender : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit defender(std::uint64_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::defender;
    }

    void prepare(std::uint64_t for_index) override;
    void use(std::uint64_t index_on);

private:
    const int damage{8};
    std::vector<std::pair<std::uint64_t, std::uint64_t>> callbacks_ids;
};


#endif //PIGEONWAR_DEFENDER_H
