#ifndef INVISIBILITY_H
#define INVISIBILITY_H

#include "caster_target_ability.h"
#include "core/turn_system.h"

class invisibility final : public caster_target_ability
{
public:
	explicit invisibility(std::uint64_t id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::invisibility;
	}

	std::string hint() const override;

private:
	void use(std::uint64_t on_index) override;
	void hide_me();
	void show_me();
private:
	bool used_{false};
	std::uint64_t entity_id;
	std::uint64_t index{0};
	std::int32_t turn_counter_{0};
	std::int32_t duration{2};
	using receiver_type = turn::turn_system::strong_receiver;
	receiver_type receiver;
};

#endif