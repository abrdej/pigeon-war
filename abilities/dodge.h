//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DODGE_H
#define PIGEONWAR_DODGE_H

#include "ability.h"

class dodge final : public ability
{
public:
	explicit dodge(std::size_t entity_id);

private:
	void prepare(size_t for_index) override {}

private:

};


#endif //PIGEONWAR_DODGE_H
