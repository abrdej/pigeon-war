#ifndef INVISIBILITY_H
#define INVISIBILITY_H

#include "caster_target_ability.h"
#include "core/turn_system.h"

class invisibility final : public caster_target_ability
{
public:
	explicit invisibility(std::uint32_t id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::invisibility;
	}

	std::string hint() const override;

private:
	void use(std::uint32_t on_index) override;
	void hide_me();
	void show_me();
private:
	bool used_{false};
	std::uint32_t entity_id;
	std::uint32_t index{0};
	std::int32_t turn_counter_{0};
	std::int32_t duration{2};
	callback_holder invisibility_callback;
};

#endif