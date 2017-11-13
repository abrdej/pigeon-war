#ifndef DAMAGE_RECEIVERS_H
#define DAMAGE_RECEIVERS_H

#include <cstdlib>

class entity_manager;

namespace damage_receivers
{
	void standard_damage_receiver(entity_manager& entity_manager, std::size_t entity_id, int damage);
	void standard_entity_remover(std::size_t entity_id);
}

class damage_receiver final
{
public:
	void receive_damage();
private:

};

#endif