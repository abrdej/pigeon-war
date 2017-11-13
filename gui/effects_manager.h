#ifndef EFECTS_MANAGER_H
#define EFECTS_MANAGER_H

#include "managers/managers.h"
#include "core/turn.h"
#include <functional>

class effects_manager : public base_manager<int, int>
{
public:
	using effect_callback = std::function<void(size_t)>;

	static void apply_every_turn_effects_for(size_t entity_id, const effect_callback& effect_callback)
	{
		//turn::turn_system::on_turn()
	}

};


#endif