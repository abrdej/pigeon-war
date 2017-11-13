#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include "core/module_holder.h"
#include "abilities/abilities.h"

static const int indestructible = std::numeric_limits<int>::max();

struct entity_definition
{
	enum class directions { right, left };
	explicit entity_definition(const std::type_index& type)
			: type(type) {}
	std::type_index type;
	std::string name;
	int health;
	abilities entity_abilities;
	directions direction;
};

namespace entity_helper
{
inline entity_definition turned_right(entity_definition&& data)
{
	data.direction = entity_definition::directions::right;
	return data;
}
inline entity_definition turned_left(entity_definition&& data)
{
	data.direction = entity_definition::directions::left;
	return data;
}
};

/*
class entity : public molude_holder
{
protected:
	entity()
		: turn_(turn_types::right) {}
	virtual ~entity(){}

public:
	enum class turn_types { right, left };
	std::wstring name() const { return name_; }
	turn_types turn() const { return turn_; }
	void turn(turn_types to_turn) { turn_ = to_turn; }

protected:
	std::wstring name_;
	turn_types turn_;
};
*/
#endif