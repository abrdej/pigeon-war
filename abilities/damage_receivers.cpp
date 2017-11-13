#include "damage_receivers.h"
#include "managers/entity_manager.h"
#include "core/board.h"

namespace damage_receivers
{
	void standard_damage_receiver(entity_manager& entity_manager, size_t entity_id, int damage)
	{
		//auto& health = entity_manager.entity_health(entity_id);
		healths_manager::receive_damage(entity_id, damage);
		//health -= damage;
		//if (health <= 0)
		//	standard_entity_remover(entity_id);
	}

	void standard_entity_remover(size_t entity_id)
	{
		//board.remove(entity_index);
	}
}