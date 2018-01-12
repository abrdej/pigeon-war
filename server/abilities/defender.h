//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_DEFENDER_H
#define PIGEONWAR_DEFENDER_H

#include "ability.h"
#include "core/turn.h"

class defender : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit defender(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::defender;
    }

    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on);

private:
    const int damage{8};
    std::vector<std::pair<sf::Uint64, sf::Uint64>> callbacks_ids;
};


#endif //PIGEONWAR_DEFENDER_H
