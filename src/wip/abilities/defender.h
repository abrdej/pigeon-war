//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_DEFENDER_H
#define PIGEONWAR_DEFENDER_H

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>

class defender : public active_ability, protected turn_callback_helper {
public:
    explicit defender(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "defender";
    }

    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on);

private:
    const int damage{8};
    std::vector<std::pair<std::uint32_t, std::uint32_t>> callbacks_ids;
};


#endif //PIGEONWAR_DEFENDER_H
