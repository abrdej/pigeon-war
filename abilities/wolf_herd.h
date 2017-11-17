//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_WOLF_HERD_H
#define PIGEONWAR_WOLF_HERD_H

#include "abilities/ability.h"

class wolf_herd final : public ability {
public:
	void prepare(size_t for_index) override;
	void use(size_t index_on);

private:
	bool used_{false};
};


#endif //PIGEONWAR_WOLF_HERD_H