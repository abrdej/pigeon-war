//
// Created by abrde on 28.01.2018.
//

#ifndef PIGEONWAR_USELESSNESS_H
#define PIGEONWAR_USELESSNESS_H

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class uselessness : public path_target_ability {
public:
    explicit uselessness(std::uint32_t entity_id);

    ~uselessness() override;

    bitmap_key get_name() const override {
        return "uselessness";
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

    std::uint32_t entity_id;
    std::int32_t damage_reduction_for_power{1};
    bool used{false};

    static const std::uint32_t no_entity_with_uselessness = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t entity_id_with_uselessness{no_entity_with_uselessness};
};


#endif //PIGEONWAR_USELESSNESS_H
