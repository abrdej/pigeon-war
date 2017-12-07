#ifndef INVISIBILITY_H
#define INVISIBILITY_H

#include "abilities/ability.h"
#include "core/turn.h"

class invisibility final : public ability 
{
public:
	explicit invisibility(size_t id);
private:
	void prepare(size_t for_index) override;
	void use(size_t on_index);
	void hide_me();
	void show_me();
private:
	bool used_{false};
	size_t entity_id;
	size_t index{0};
	size_t turn_counter_{0};
	using receiver_type = turn::turn_system::strong_receiver;
	receiver_type receiver;
};

#endif