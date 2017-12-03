//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_SHILED_H
#define PIGEONWAR_SHILED_H

#include "ability.h"

class shield : public ability {
public:
    explicit shield(std::size_t entity_id);

private:
    void prepare(size_t for_index) override {}
    float range_attack_reduction{0.5f};
};

#endif //PIGEONWAR_SHILED_H
