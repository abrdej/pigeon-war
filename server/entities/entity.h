#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include "core/module_holder.h"

#include "common/health_field.h"
#include "common/bitmap_field.h"

enum class directions { right, left };

struct base_entity : module_holder {
	static constexpr uint32_t no_id{ std::numeric_limits<uint32_t>::max()};
	uint32_t entity_id{no_id};

	std::string name;
};

#endif