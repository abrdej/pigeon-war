//
// Created by abrde on 20.01.2018.
//

#ifndef PIGEONWAR_SUCK_THE_SOUL_H
#define PIGEONWAR_SUCK_THE_SOUL_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class suck_the_soul final : public neighboring_target_ability<>,
                            per_turn_usable
{
public:
    explicit suck_the_soul(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::drain;
    }

    //std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage{10};
    const std::int32_t duration{3};
    const std::int32_t suck_amount{5};

    std::vector<std::pair<std::uint32_t, std::int32_t>> souls;
    std::unordered_map<std::uint32_t, std::size_t> souls_mapped;
};


#endif //PIGEONWAR_SUCK_THE_SOUL_H
