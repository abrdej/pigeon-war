//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_TELEPORT_H
#define PIGEONWAR_TELEPORT_H

#include "abilities/ability.h"

class teleport final : public ability
{
public:
	teleport() = default;
private:
	void prepare(size_t for_index) override;
	void use(size_t for_index, size_t index_on);

private:
	bool used{false};
};


#endif //PIGEONWAR_TELEPORT_H
