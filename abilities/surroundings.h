//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SURROUNDINGS_H
#define PIGEONWAR_SURROUNDINGS_H

#include "ability.h"

class surroundings : public ability {
public:
    explicit surroundings(std::size_t entity_id);

private:
    void prepare(size_t for_index) override {}
    int damage_reduction{3};
    int min_damage{3};
};

#endif //PIGEONWAR_SURROUNDINGS_H
