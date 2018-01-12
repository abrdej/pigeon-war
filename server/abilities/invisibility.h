#ifndef INVISIBILITY_H
#define INVISIBILITY_H

#include "caster_target_ability.h"
#include "core/turn.h"

class invisibility final : public caster_target_ability
{
public:
	explicit invisibility(sf::Uint64 id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::invisibility;
	}

	std::string hint() const override;

private:
	void use(sf::Uint64 on_index) override;
	void hide_me();
	void show_me();
private:
	bool used_{false};
	sf::Uint64 entity_id;
	sf::Uint64 index{0};
	sf::Int32 turn_counter_{0};
	sf::Int32 duration{2};
	using receiver_type = turn::turn_system::strong_receiver;
	receiver_type receiver;
};

#endif