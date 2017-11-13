#ifndef ABILITIES_MANAGER_H
#define ABILITIES_MANAGER_H

#include "managers.h"
#include "core/board.h"
#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "abilities/moveable.h"
#include <unordered_map>
#include <vector>

class abilities_manager : public base_manager<abilities, abilities&>
{
public:
	using moving_manager = base_manager<moveable, moveable&>;

	//enum class abilities_types { moving, offensive, defensive, special, passive};

	//static void init(size_t board_index, abilities_types ability_type)
	//{
		//if (ability_type == abilities_types::moving)
		//{
		//	moving_manager::component_for(board::at(board_index))(board_index);
		//}
	//}
};

#endif