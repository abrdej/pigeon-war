#ifndef BASIC_MELEE_ATTACK_H
#define BASIC_MELEE_ATTACK_H

#include "abilities/ability.h"

class basic_melee_attack final : public ability
{
public:
	basic_melee_attack();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);
	
private:
	static const size_t range_ = 1;
	static const size_t damage_ = 4;
};

#endif