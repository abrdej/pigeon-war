//
// Created by abrdej on 18.01.18.
//

#ifndef PIGEONWAR_DRAWER_FACOTRY_H
#define PIGEONWAR_DRAWER_FACOTRY_H

#include "drawable.h"

struct drawer_factory {
	static std::shared_ptr<drawable> create(std::uint32_t entity_id, const std::string& entity_name);
};


#endif //PIGEONWAR_DRAWER_FACOTRY_H
