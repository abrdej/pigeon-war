//
// Created by abrdej on 29.01.18.
//

#ifndef PIGEONWAR_METEORITE_H
#define PIGEONWAR_METEORITE_H

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class meteorite : public active_ability, per_turn_usable {
public:
    explicit meteorite(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "meteorite";
    }

    std::string hint() const override;

    void prepare(std::uint32_t for_index) override;

private:
    void use(std::uint32_t index_on);

    std::uint32_t entity_id;
    std::int32_t damage{18};
    std::int32_t power_cost{12};

    turn_scoped_connection meteorite_holder;
};

#endif //PIGEONWAR_METEORITE_H
