#ifndef INVISIBILITY_H
#define INVISIBILITY_H

#include "abilities/ability.h"
#include "core/event_center.h"

class invisibility final : public ability 
{
public:
	invisibility();
private:
	void prepare(size_t for_index) override;
	void use(size_t on_index);
	void hide_me(size_t my_index);
	void show_me(size_t my_index);
private:
	bool used_;
	size_t turn_counter_;
	size_t my_id_;
};

#endif